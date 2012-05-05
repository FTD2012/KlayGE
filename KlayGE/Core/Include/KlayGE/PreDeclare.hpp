#ifndef _PREDECLARE_HPP
#define _PREDECLARE_HPP

#pragma once

#ifdef KLAYGE_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 6011)
#endif
#include <boost/smart_ptr.hpp>
#ifdef KLAYGE_COMPILER_MSVC
#pragma warning(pop)
#endif

namespace KlayGE
{
	struct ContextCfg;
	class Context;
	class ResIdentifier;
	typedef boost::shared_ptr<ResIdentifier> ResIdentifierPtr;
	class ResLoadingDesc;
	typedef boost::shared_ptr<ResLoadingDesc> ResLoadingDescPtr;
	class ResLoader;

	class XMLDocument;
	typedef boost::shared_ptr<XMLDocument> XMLDocumentPtr;
	class XMLNode;
	typedef boost::shared_ptr<XMLNode> XMLNodePtr;
	class XMLAttribute;
	typedef boost::shared_ptr<XMLAttribute> XMLAttributePtr;

	class half;
	template <typename T, int N>
	class Vector_T;
	typedef Vector_T<int32_t, 1> int1;
	typedef Vector_T<int32_t, 2> int2;
	typedef Vector_T<int32_t, 3> int3;
	typedef Vector_T<int32_t, 4> int4;
	typedef Vector_T<uint32_t, 1> uint1;
	typedef Vector_T<uint32_t, 2> uint2;
	typedef Vector_T<uint32_t, 3> uint3;
	typedef Vector_T<uint32_t, 4> uint4;
	typedef Vector_T<float, 1> float1;
	typedef Vector_T<float, 2> float2;
	typedef Vector_T<float, 3> float3;
	typedef Vector_T<float, 4> float4;
	template <typename T>
	class Size_T;
	typedef Size_T<float> Size;
	template <typename T>
	class Rect_T;
	typedef Rect_T<float> Rect;
	template <typename T>
	class Matrix4_T;
	typedef Matrix4_T<float> float4x4;
	template <typename T>
	class Quaternion_T;
	typedef Quaternion_T<float> Quaternion;
	template <typename T>
	class Plane_T;
	typedef Plane_T<float> Plane;
	template <typename T>
	class Color_T;
	typedef Color_T<float> Color;
	template <typename T>
	class Bound_T;
	typedef Bound_T<float> Bound;
	template <typename T>
	class Sphere_T;
	typedef Sphere_T<float> Sphere;
	template <typename T>
	class AABBox_T;
	typedef AABBox_T<float> AABBox;
	template <typename T>
	class Frustum_T;
	typedef Frustum_T<float> Frustum;
	template <typename T>
	class OBBox_T;
	typedef OBBox_T<float> OBBox;

	class SceneManager;
	typedef boost::shared_ptr<SceneManager> SceneManagerPtr;
	class SceneNode;
	typedef boost::shared_ptr<SceneNode> SceneNodePtr;
	class SceneObject;
	typedef boost::shared_ptr<SceneObject> SceneObjectPtr;
	class SceneObjectHelper;
	typedef boost::shared_ptr<SceneObjectHelper> SceneObjectHelperPtr;
	class SceneObjectSkyBox;
	typedef boost::shared_ptr<SceneObjectSkyBox> SceneObjectSkyBoxPtr;
	class SceneObjectHDRSkyBox;
	typedef boost::shared_ptr<SceneObjectHDRSkyBox> SceneObjectHDRSkyBoxPtr;
	class SceneObjectLightSourceProxy;
	typedef boost::shared_ptr<SceneObjectLightSourceProxy> SceneObjectLightSourceProxyPtr;
	class SceneObjectCameraProxy;
	typedef boost::shared_ptr<SceneObjectCameraProxy> SceneObjectCameraProxyPtr;

	struct ElementInitData;
	class Camera;
	typedef boost::shared_ptr<Camera> CameraPtr;
	class FirstPersonCameraController;
	class Font;
	typedef boost::shared_ptr<Font> FontPtr;
	class RenderEngine;
	typedef boost::shared_ptr<RenderEngine> RenderEnginePtr;
	struct RenderSettings;
	struct RenderMaterial;
	typedef boost::shared_ptr<RenderMaterial> RenderMaterialPtr;
	class Renderable;
	typedef boost::shared_ptr<Renderable> RenderablePtr;
	class RenderableHelper;
	typedef boost::shared_ptr<RenderableHelper> RenderableHelperPtr;
	class RenderablePoint;
	typedef boost::shared_ptr<RenderablePoint> RenderablePointPtr;
	class RenderableLine;
	typedef boost::shared_ptr<RenderableLine> RenderableLinePtr;
	class RenderableTriangle;
	typedef boost::shared_ptr<RenderableTriangle> RenderableTrianglePtr;
	class RenderableTriBox;
	typedef boost::shared_ptr<RenderableTriBox> RenderableTriBoxPtr;
	class RenderableLineBox;
	typedef boost::shared_ptr<RenderableLineBox> RenderableLineBoxPtr;
	class RenderableSkyBox;
	typedef boost::shared_ptr<RenderableSkyBox> RenderableSkyBoxPtr;
	class RenderableHDRSkyBox;
	typedef boost::shared_ptr<RenderableHDRSkyBox> RenderableHDRSkyBoxPtr;
	class RenderablePlane;
	typedef boost::shared_ptr<RenderablePlane> RenderablePlanePtr;
	class RenderEffect;
	typedef boost::shared_ptr<RenderEffect> RenderEffectPtr;
	class RenderTechnique;
	typedef boost::shared_ptr<RenderTechnique> RenderTechniquePtr;
	class RenderPass;
	typedef boost::shared_ptr<RenderPass> RenderPassPtr;
	class RenderEffectParameter;
	typedef boost::shared_ptr<RenderEffectParameter> RenderEffectParameterPtr;
	class RenderVariable;
	typedef boost::shared_ptr<RenderVariable> RenderVariablePtr;
	class RenderEffectAnnotation;
	typedef boost::shared_ptr<RenderEffectAnnotation> RenderEffectAnnotationPtr;
	struct RasterizerStateDesc;
	struct DepthStencilStateDesc;
	struct BlendStateDesc;
	struct SamplerStateDesc;
	class RasterizerStateObject;
	typedef boost::shared_ptr<RasterizerStateObject> RasterizerStateObjectPtr;
	class DepthStencilStateObject;
	typedef boost::shared_ptr<DepthStencilStateObject> DepthStencilStateObjectPtr;
	class BlendStateObject;
	typedef boost::shared_ptr<BlendStateObject> BlendStateObjectPtr;
	class SamplerStateObject;
	typedef boost::shared_ptr<SamplerStateObject> SamplerStateObjectPtr;
	class ShaderObject;
	typedef boost::shared_ptr<ShaderObject> ShaderObjectPtr;
	class Texture;
	typedef boost::shared_ptr<Texture> TexturePtr;
	class JudaTexture;
	typedef boost::shared_ptr<JudaTexture> JudaTexturePtr;
	class FrameBuffer;
	typedef boost::shared_ptr<FrameBuffer> FrameBufferPtr;
	class RenderView;
	typedef boost::shared_ptr<RenderView> RenderViewPtr;
	class GraphicsBuffer;
	typedef boost::shared_ptr<GraphicsBuffer> GraphicsBufferPtr;
	class RenderLayout;
	typedef boost::shared_ptr<RenderLayout> RenderLayoutPtr;
	class RenderGraphicsBuffer;
	typedef boost::shared_ptr<RenderGraphicsBuffer> RenderGraphicsBufferPtr;
	struct Viewport;
	class RenderFactory;
	typedef boost::shared_ptr<RenderFactory> RenderFactoryPtr;
	class RenderModel;
	typedef boost::shared_ptr<RenderModel> RenderModelPtr;
	class StaticMesh;
	typedef boost::shared_ptr<StaticMesh> StaticMeshPtr;
	class SkinnedModel;
	typedef boost::shared_ptr<SkinnedModel> SkinnedModelPtr;
	class SkinnedMesh;
	typedef boost::shared_ptr<SkinnedMesh> SkinnedMeshPtr;
	class RenderableLightSourceProxy;
	typedef boost::shared_ptr<RenderableLightSourceProxy> RenderableLightSourceProxyPtr;
	class LightSource;
	typedef boost::shared_ptr<LightSource> LightSourcePtr;
	class AmbientLightSource;
	typedef boost::shared_ptr<AmbientLightSource> AmbientLightSourcePtr;
	class PointLightSource;	
	typedef boost::shared_ptr<PointLightSource> PointLightSourcePtr;
	class SpotLightSource;
	typedef boost::shared_ptr<SpotLightSource> SpotLightSourcePtr;
	class DirectionalLightSource;
	typedef boost::shared_ptr<DirectionalLightSource> DirectionalLightSourcePtr;
	struct RenderDeviceCaps;
	class Query;
	typedef boost::shared_ptr<Query> QueryPtr;
	class OcclusionQuery;
	typedef boost::shared_ptr<OcclusionQuery> OcclusionQueryPtr;
	class ConditionalRender;
	typedef boost::shared_ptr<ConditionalRender> ConditionalRenderPtr;
	class PostProcess;
	typedef boost::shared_ptr<PostProcess> PostProcessPtr;
	class PostProcessChain;
	typedef boost::shared_ptr<PostProcessChain> PostProcessChainPtr;
	class SeparableBoxFilterPostProcess;
	typedef boost::shared_ptr<SeparableBoxFilterPostProcess> SeparableBoxFilterPostProcessPtr;
	class SeparableGaussianFilterPostProcess;
	typedef boost::shared_ptr<SeparableGaussianFilterPostProcess> SeparableGaussianFilterPostProcessPtr;
	class SeparableBilateralFilterPostProcess;
	typedef boost::shared_ptr<SeparableBilateralFilterPostProcess> SeparableBilateralFilterPostProcessPtr;
	template <typename T>
	class BlurPostProcess;
	class SumLumPostProcess;
	typedef boost::shared_ptr<SumLumPostProcess> SumLumPostProcessPtr;
	class SumLumLogPostProcess;
	typedef boost::shared_ptr<SumLumLogPostProcess> SumLumLogPostProcessPtr;
	class SumLumLogPostProcessCS;
	typedef boost::shared_ptr<SumLumLogPostProcess> SumLumLogPostProcessCSPtr;
	class SumLumIterativePostProcess;
	typedef boost::shared_ptr<SumLumIterativePostProcess> SumLumIterativePostProcessPtr;
	class AdaptedLumPostProcess;
	typedef boost::shared_ptr<AdaptedLumPostProcess> AdaptedLumPostProcessPtr;
	class AdaptedLumPostProcessCS;
	typedef boost::shared_ptr<AdaptedLumPostProcessCS> AdaptedLumPostProcessCSPtr;
	class ImageStatPostProcess;
	typedef boost::shared_ptr<ImageStatPostProcess> ImageStatPostProcessPtr;
	class LensEffectsPostProcess;
	typedef boost::shared_ptr<LensEffectsPostProcess> LensEffectsPostProcessPtr;
	class LensEffectsPostProcessCS;
	typedef boost::shared_ptr<LensEffectsPostProcessCS> LensEffectsPostProcessCSPtr;
	class ToneMappingPostProcess;
	typedef boost::shared_ptr<ToneMappingPostProcess> ToneMappingPostProcessPtr;
	class HDRPostProcess;
	typedef boost::shared_ptr<HDRPostProcess> HDRPostProcessPtr;
	class SATSeparableScanSweepPostProcess;
	typedef boost::shared_ptr<SATSeparableScanSweepPostProcess> SATSeparableScanSweepPostProcessPtr;
	class SummedAreaTablePostProcess;
	typedef boost::shared_ptr<SummedAreaTablePostProcess> SummedAreaTablePostProcessPtr;
	class TAAPostProcess;
	typedef boost::shared_ptr<TAAPostProcess> TAAPostProcessPtr;
	class SSVOPostProcess;
	typedef boost::shared_ptr<SSVOPostProcess> SSVOPostProcessPtr;
	template <typename ParticleType>
	class ParticleSystem;
	class InfTerrainRenderable;
	class InfTerrainSceneObject;
	class LensFlareRenderable;
	class LensFlareSceneObject;
	class DeferredRenderingLayer;
	typedef boost::shared_ptr<DeferredRenderingLayer> DeferredRenderingLayerPtr;
	class GpuFft;
	typedef boost::shared_ptr<GpuFft> GpuFftPtr;
	class GpuFftPS;
	typedef boost::shared_ptr<GpuFftPS> GpuFftPSPtr;
	class GpuFftCS4;
	typedef boost::shared_ptr<GpuFftCS4> GpuFftCS4Ptr;
	class GpuFftCS5;
	typedef boost::shared_ptr<GpuFftCS4> GpuFftCS5Ptr;
	class SSGIPostProcess;
	typedef boost::shared_ptr<SSGIPostProcess> SSGIPostProcessPtr;
	class SSRPostProcess;
	typedef boost::shared_ptr<SSRPostProcess> SSRPostProcessPtr;

	class UIManager;
	typedef boost::shared_ptr<UIManager> UIManagerPtr;
	class UIElement;
	typedef boost::shared_ptr<UIElement> UIElementPtr;
	class UIControl;
	typedef boost::shared_ptr<UIControl> UIControlPtr;
	class UIDialog;
	typedef boost::shared_ptr<UIDialog> UIDialogPtr;
	class UIStatic;
	typedef boost::shared_ptr<UIStatic> UIStaticPtr;
	class UIButton;
	typedef boost::shared_ptr<UIButton> UIButtonPtr;
	class UITexButton;
	typedef boost::shared_ptr<UITexButton> UITexButtonPtr;
	class UICheckBox;
	typedef boost::shared_ptr<UICheckBox> UICheckBoxPtr;
	class UIRadioButton;
	typedef boost::shared_ptr<UIRadioButton> UIRadioButtonPtr;
	class UISlider;
	typedef boost::shared_ptr<UISlider> UISliderPtr;
	class UIScrollBar;
	typedef boost::shared_ptr<UIScrollBar> UIScrollBarPtr;
	class UIListBox;
	typedef boost::shared_ptr<UIListBox> UIListBoxPtr;
	class UIComboBox;
	typedef boost::shared_ptr<UIComboBox> UIComboBoxPtr;
	class UIEditBox;
	typedef boost::shared_ptr<UIEditBox> UIEditBoxPtr;
	class UIPolylineEditBox;
	typedef boost::shared_ptr<UIPolylineEditBox> UIPolylineEditBoxPtr;
	class UIProgressBar;
	typedef boost::shared_ptr<UIProgressBar> UIProgressBarPtr;

	class Socket;
	class Lobby;
	class Player;

	class AudioEngine;
	typedef boost::shared_ptr<AudioEngine> AudioEnginePtr;
	class AudioBuffer;
	typedef boost::shared_ptr<AudioBuffer> AudioBufferPtr;
	class SoundBuffer;
	class MusicBuffer;
	class AudioDataSource;
	typedef boost::shared_ptr<AudioDataSource> AudioDataSourcePtr;
	class AudioFactory;
	typedef boost::shared_ptr<AudioFactory> AudioFactoryPtr;
	class AudioDataSourceFactory;
	typedef boost::shared_ptr<AudioDataSourceFactory> AudioDataSourceFactoryPtr;

	class App3DFramework;
	class Window;
	typedef boost::shared_ptr<Window> WindowPtr;

	class InputEngine;
	typedef boost::shared_ptr<InputEngine> InputEnginePtr;
	class InputDevice;
	typedef boost::shared_ptr<InputDevice> InputDevicePtr;
	class InputKeyboard;
	typedef boost::shared_ptr<InputKeyboard> InputKeyboardPtr;
	class InputMouse;
	typedef boost::shared_ptr<InputMouse> InputMousePtr;
	class InputJoystick;
	typedef boost::shared_ptr<InputJoystick> InputJoystickPtr;
	class InputFactory;
	typedef boost::shared_ptr<InputFactory> InputFactoryPtr;

	class ShowEngine;
	typedef boost::shared_ptr<ShowEngine> ShowEnginePtr;
	class ShowFactory;
	typedef boost::shared_ptr<ShowFactory> ShowFactoryPtr;

	class ScriptModule;
	class RegisterModule;
	class ScriptEngine;

	class LZMACodec;
}

#endif			// _PREDECLARE_HPP
