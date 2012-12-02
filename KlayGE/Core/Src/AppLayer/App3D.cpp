// App3D.cpp
// KlayGE App3D类 实现文件
// Ver 3.8.0
// 版权所有(C) 龚敏敏, 2003-2008
// Homepage: http://www.klayge.org
//
// 3.8.0
// 移入Core (2008.10.16)
//
// 3.7.0
// 改进了Update (2007.8.14)
//
// 3.6.0
// 增加了MakeWindow (2007.6.26)
//
// 3.1.0
// 增加了OnResize (2005.11.20)
//
// 2.7.0
// 增加了Quit (2005.6.28)
//
// 2.0.0
// 初次建立 (2003.7.10)
//
// 修改记录
/////////////////////////////////////////////////////////////////////////////////

#include <KlayGE/KlayGE.hpp>
#include <KlayGE/Util.hpp>
#include <KlayGE/ThrowErr.hpp>
#include <KlayGE/Math.hpp>
#include <KlayGE/Context.hpp>
#include <KlayGE/RenderEngine.hpp>
#include <KlayGE/RenderFactory.hpp>
#include <KlayGE/RenderSettings.hpp>
#include <KlayGE/FrameBuffer.hpp>
#include <KlayGE/Window.hpp>
#include <KlayGE/Camera.hpp>
#include <KlayGE/UI.hpp>
#include <KlayGE/SceneManager.hpp>
#include <KlayGE/DeferredRenderingLayer.hpp>

#include <boost/assert.hpp>

#include <KlayGE/App3D.hpp>

#ifdef KLAYGE_PLATFORM_WINDOWS_METRO
#include <ppl.h>
#include <ppltasks.h>

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::Foundation;
using namespace concurrency;
#endif

namespace KlayGE
{
#if defined KLAYGE_PLATFORM_WINDOWS_METRO
	ref class MetroFrameworkSource;

	ref class MetroFramework sealed : public Windows::ApplicationModel::Core::IFrameworkView
	{
		friend class App3DFramework;
		friend MetroFrameworkSource;

	public:
		MetroFramework();
	
		virtual void Initialize(Windows::ApplicationModel::Core::CoreApplicationView^ application_view);
		virtual void SetWindow(Windows::UI::Core::CoreWindow^ window);
		virtual void Load(Platform::String^ entryPoint);
		virtual void Run();
		virtual void Uninitialize();

	private:
		void OnActivated(Windows::ApplicationModel::Core::CoreApplicationView^ application_view, Windows::ApplicationModel::Activation::IActivatedEventArgs^ args);
		void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
		void OnResuming(Platform::Object^ sender, Platform::Object^ args);

		void BindAppFramework(App3DFramework* app);

	private:
		App3DFramework* app_;
	};

	ref class MetroFrameworkSource sealed : Windows::ApplicationModel::Core::IFrameworkViewSource
	{
		friend class App3DFramework;

	public:
		virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView();

	private:
		void BindAppFramework(App3DFramework* app);

	private:
		App3DFramework* app_;
	};

	MetroFramework::MetroFramework()
	{
	}

	void MetroFramework::Initialize(CoreApplicationView^ application_view)
	{
		application_view->Activated +=
			ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &MetroFramework::OnActivated);

		CoreApplication::Suspending +=
			ref new EventHandler<SuspendingEventArgs^>(this, &MetroFramework::OnSuspending);

		CoreApplication::Resuming +=
			ref new EventHandler<Platform::Object^>(this, &MetroFramework::OnResuming);
	}

	void MetroFramework::SetWindow(CoreWindow^ window)
	{
		app_->MainWnd()->SetWindow(CoreWindow::GetForCurrentThread());
		app_->MetroCreate();
	}

	void MetroFramework::Load(Platform::String^ entryPoint)
	{
	}

	void MetroFramework::Run()
	{
		app_->MetroRun();
	}

	void MetroFramework::Uninitialize()
	{
	}

	void MetroFramework::OnActivated(CoreApplicationView^ application_view, IActivatedEventArgs^ args)
	{
		CoreWindow::GetForCurrentThread()->Activate();
	}

	void MetroFramework::OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
	{
		SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();

		create_task([this, deferral]()
		{
			// Insert your code here.

			deferral->Complete();
		});
	}

	void MetroFramework::OnResuming(Platform::Object^ sender, Platform::Object^ args)
	{
	}

	void MetroFramework::BindAppFramework(App3DFramework* app)
	{
		app_ = app;
	}
	
	IFrameworkView^ MetroFrameworkSource::CreateView()
	{
		MetroFramework^ ret = ref new MetroFramework;
		ret->BindAppFramework(app_);
		return ret;
	}

	void MetroFrameworkSource::BindAppFramework(App3DFramework* app)
	{
		app_ = app;
	}
#endif

	// 构造函数
	/////////////////////////////////////////////////////////////////////////////////
	App3DFramework::App3DFramework(std::string const & name)
						: name_(name),
							fps_(0), accumulate_time_(0), num_frames_(0),
							app_time_(0), frame_time_(0)
	{
		Context::Instance().AppInstance(*this);

		ContextCfg cfg = Context::Instance().Config();
		main_wnd_ = this->MakeWindow(name_, cfg.graphics_cfg);
#ifndef KLAYGE_PLATFORM_WINDOWS_METRO
		cfg.graphics_cfg.left = main_wnd_->Left();
		cfg.graphics_cfg.top = main_wnd_->Top();
		cfg.graphics_cfg.width = main_wnd_->Width();
		cfg.graphics_cfg.height = main_wnd_->Height();
		Context::Instance().Config(cfg);
#endif
	}

	App3DFramework::~App3DFramework()
	{
		this->Destroy();

		main_wnd_.reset();
	}

	// 建立应用程序主窗口
	/////////////////////////////////////////////////////////////////////////////////
#ifdef KLAYGE_PLATFORM_WINDOWS_METRO
	void App3DFramework::Create()
	{
	}

	void App3DFramework::MetroCreate()
	{
		ContextCfg cfg = Context::Instance().Config();
		cfg.graphics_cfg.left = main_wnd_->Left();
		cfg.graphics_cfg.top = main_wnd_->Top();
		cfg.graphics_cfg.width = main_wnd_->Width();
		cfg.graphics_cfg.height = main_wnd_->Height();
		Context::Instance().Config(cfg);
#else
	void App3DFramework::Create()
	{
		ContextCfg const & cfg = Context::Instance().Config();
#endif
		Context::Instance().RenderFactoryInstance().RenderEngineInstance().CreateRenderWindow(name_,
			cfg.graphics_cfg);

		if (cfg.deferred_rendering)
		{
			Context::Instance().DeferredRenderingLayerInstance(MakeSharedPtr<DeferredRenderingLayer>());
		}

		this->InitObjects();
		this->OnResize(cfg.graphics_cfg.width, cfg.graphics_cfg.height);
	}

	void App3DFramework::Destroy()
	{
		this->DelObjects();

		Context::Instance().SceneManagerInstance(SceneManagerPtr());
		Context::Instance().AudioFactoryInstance(AudioFactoryPtr());
		Context::Instance().ShowFactoryInstance(ShowFactoryPtr());

		UIManager::ForceDestroy();
		Context::Instance().DeferredRenderingLayerInstance(DeferredRenderingLayerPtr());
		Context::Instance().RenderFactoryInstance(RenderFactoryPtr());
	}

	WindowPtr App3DFramework::MakeWindow(std::string const & name, RenderSettings const & settings)
	{
		return MakeSharedPtr<Window>(name, settings);
	}

#if defined KLAYGE_PLATFORM_WINDOWS_METRO
	void App3DFramework::Run()
	{
		MetroFrameworkSource^ metro_app = ref new MetroFrameworkSource;
		metro_app->BindAppFramework(this);
		CoreApplication::Run(metro_app);
	}

	void App3DFramework::MetroRun()
#else
	void App3DFramework::Run()
#endif
	{
		Context::Instance().RenderFactoryInstance().RenderEngineInstance().StartRendering();

		this->DelObjects();
	}

	// 获取当前摄像机
	/////////////////////////////////////////////////////////////////////////////////
	Camera const & App3DFramework::ActiveCamera() const
	{
		RenderEngine& re = Context::Instance().RenderFactoryInstance().RenderEngineInstance();
		CameraPtr const & camera = re.CurFrameBuffer()->GetViewport()->camera;
		BOOST_ASSERT(camera);

		return *camera;
	}

	Camera& App3DFramework::ActiveCamera()
	{
		RenderEngine& re = Context::Instance().RenderFactoryInstance().RenderEngineInstance();
		CameraPtr const & camera = re.CurFrameBuffer()->GetViewport()->camera;
		BOOST_ASSERT(camera);

		return *camera;
	}

	// 设置观察矩阵
	/////////////////////////////////////////////////////////////////////////////////
	void App3DFramework::LookAt(float3 const & vEye, float3 const & vLookAt)
	{
		this->ActiveCamera().ViewParams(vEye, vLookAt, float3(0, 1, 0));
	}

	void App3DFramework::LookAt(float3 const & vEye, float3 const & vLookAt,
												float3 const & vUp)
	{
		this->ActiveCamera().ViewParams(vEye, vLookAt, vUp);
	}

	// 设置投射矩阵
	/////////////////////////////////////////////////////////////////////////////////
	void App3DFramework::Proj(float nearPlane, float farPlane)
	{
		BOOST_ASSERT(nearPlane != 0);
		BOOST_ASSERT(farPlane != 0);
		BOOST_ASSERT(farPlane > nearPlane);

		RenderEngine& re = Context::Instance().RenderFactoryInstance().RenderEngineInstance();
		FrameBuffer& fb = *re.CurFrameBuffer();

		this->ActiveCamera().ProjParams(PI / 4, static_cast<float>(fb.Width()) / fb.Height(),
			nearPlane, farPlane);
 	}

	// 退出程序
	/////////////////////////////////////////////////////////////////////////////////
	void App3DFramework::Quit()
	{
#ifdef KLAYGE_PLATFORM_WINDOWS
#ifdef KLAYGE_PLATFORM_WINDOWS_DESKTOP
		::PostQuitMessage(0);
#endif
#else
		exit(0);
#endif
	}

	// 更新场景
	/////////////////////////////////////////////////////////////////////////////////
	uint32_t App3DFramework::Update(uint32_t pass)
	{
		if (0 == pass)
		{
			this->UpdateStats();
			this->DoUpdateOverlay();
		}

		return this->DoUpdate(pass);
	}

	// 响应窗口大小变化
	/////////////////////////////////////////////////////////////////////////////////
	void App3DFramework::OnResize(uint32_t /*width*/, uint32_t /*height*/)
	{
		this->Proj(this->ActiveCamera().NearPlane(), this->ActiveCamera().FarPlane());
	}

	// 更新状态
	/////////////////////////////////////////////////////////////////////////////////
	void App3DFramework::UpdateStats()
	{
		// measure statistics
		frame_time_ = static_cast<float>(timer_.elapsed());
		++ num_frames_;
		accumulate_time_ += frame_time_;
		app_time_ += frame_time_;

		// check if new second
		if (accumulate_time_ > 1)
		{
			// new second - not 100% precise
			fps_ = num_frames_ / accumulate_time_;

			accumulate_time_ = 0;
			num_frames_  = 0;
		}

		timer_.restart();
	}

	// 获取渲染目标的每秒帧数
	/////////////////////////////////////////////////////////////////////////////////
	float App3DFramework::FPS() const
	{
		return fps_;
	}

	float App3DFramework::AppTime() const
	{
		return app_time_;
	}

	float App3DFramework::FrameTime() const
	{
		return frame_time_;
	}
}
