// D3D11Texture.cpp
// KlayGE D3D11纹理类 实现文件
// Ver 3.8.0
// 版权所有(C) 龚敏敏, 2009
// Homepage: http://www.klayge.org
//
// 3.8.0
// 初次建立 (2009.1.30)
//
// 修改记录
/////////////////////////////////////////////////////////////////////////////////

#include <KlayGE/KlayGE.hpp>
#include <KlayGE/Util.hpp>
#include <KlayGE/COMPtr.hpp>
#include <KlayGE/ThrowErr.hpp>
#include <KlayGE/Math.hpp>
#include <KlayGE/Context.hpp>
#include <KlayGE/RenderEngine.hpp>
#include <KlayGE/RenderFactory.hpp>
#include <KlayGE/Texture.hpp>

#include <cstring>
#include <boost/assert.hpp>
#ifdef KLAYGE_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4100 6011 6334)
#endif
#include <boost/functional/hash.hpp>
#ifdef KLAYGE_COMPILER_MSVC
#pragma warning(pop)
#endif

#include <KlayGE/D3D11/D3D11MinGWDefs.hpp>
#ifdef KLAYGE_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4005)
#endif
#include <d3dx11.h>
#ifdef KLAYGE_COMPILER_MSVC
#pragma warning(pop)
#endif

#include <KlayGE/D3D11/D3D11RenderEngine.hpp>
#include <KlayGE/D3D11/D3D11Texture.hpp>

#ifdef KLAYGE_COMPILER_MSVC
#ifdef KLAYGE_DEBUG
	#pragma comment(lib, "d3dx11d.lib")
#else
	#pragma comment(lib, "d3dx11.lib")
#endif
#endif

namespace KlayGE
{
	D3D11Texture::D3D11Texture(TextureType type, uint32_t sample_count, uint32_t sample_quality, uint32_t access_hint)
					: Texture(type, sample_count, sample_quality, access_hint)
	{
		if (access_hint & EAH_GPU_Write)
		{
			BOOST_ASSERT(!(access_hint & EAH_CPU_Read));
			BOOST_ASSERT(!(access_hint & EAH_CPU_Write));
		}

		D3D11RenderEngine& renderEngine(*checked_cast<D3D11RenderEngine*>(&Context::Instance().RenderFactoryInstance().RenderEngineInstance()));
		d3d_device_ = renderEngine.D3DDevice();
		d3d_imm_ctx_ = renderEngine.D3DDeviceImmContext();
	}

	D3D11Texture::~D3D11Texture()
	{
	}

	std::wstring const & D3D11Texture::Name() const
	{
		static const std::wstring name(L"Direct3D11 Texture");
		return name;
	}

	uint32_t D3D11Texture::Width(uint32_t level) const
	{
		UNREF_PARAM(level);
		BOOST_ASSERT(level < num_mip_maps_);

		return 1;
	}

	uint32_t D3D11Texture::Height(uint32_t level) const
	{
		UNREF_PARAM(level);
		BOOST_ASSERT(level < num_mip_maps_);

		return 1;
	}

	uint32_t D3D11Texture::Depth(uint32_t level) const
	{
		UNREF_PARAM(level);
		BOOST_ASSERT(level < num_mip_maps_);

		return 1;
	}

	void D3D11Texture::CopyToSubTexture1D(Texture& /*target*/,
			uint32_t /*dst_array_index*/, uint32_t /*dst_level*/, uint32_t /*dst_x_offset*/, uint32_t /*dst_width*/,
			uint32_t /*src_array_index*/, uint32_t /*src_level*/, uint32_t /*src_x_offset*/, uint32_t /*src_width*/)
	{
		BOOST_ASSERT(false);
	}

	void D3D11Texture::CopyToSubTexture2D(Texture& /*target*/,
			uint32_t /*dst_array_index*/, uint32_t /*dst_level*/, uint32_t /*dst_x_offset*/, uint32_t /*dst_y_offset*/, uint32_t /*dst_width*/, uint32_t /*dst_height*/,
			uint32_t /*src_array_index*/, uint32_t /*src_level*/, uint32_t /*src_x_offset*/, uint32_t /*src_y_offset*/, uint32_t /*src_width*/, uint32_t /*src_height*/)
	{
		BOOST_ASSERT(false);
	}

	void D3D11Texture::CopyToSubTexture3D(Texture& /*target*/,
			uint32_t /*dst_array_index*/, uint32_t /*dst_level*/, uint32_t /*dst_x_offset*/, uint32_t /*dst_y_offset*/, uint32_t /*dst_z_offset*/, uint32_t /*dst_width*/, uint32_t /*dst_height*/, uint32_t /*dst_depth*/,
			uint32_t /*src_array_index*/, uint32_t /*src_level*/, uint32_t /*src_x_offset*/, uint32_t /*src_y_offset*/, uint32_t /*src_z_offset*/, uint32_t /*src_width*/, uint32_t /*src_height*/, uint32_t /*src_depth*/)
	{
		BOOST_ASSERT(false);
	}

	void D3D11Texture::CopyToSubTextureCube(Texture& /*target*/,
			uint32_t /*dst_array_index*/, CubeFaces /*dst_face*/, uint32_t /*dst_level*/, uint32_t /*dst_x_offset*/, uint32_t /*dst_y_offset*/, uint32_t /*dst_width*/, uint32_t /*dst_height*/,
			uint32_t /*src_array_index*/, CubeFaces /*src_face*/, uint32_t /*src_level*/, uint32_t /*src_x_offset*/, uint32_t /*src_y_offset*/, uint32_t /*src_width*/, uint32_t /*src_height*/)
	{
		BOOST_ASSERT(false);
	}

	ID3D11ShaderResourceViewPtr const & D3D11Texture::RetriveD3DShaderResourceView(uint32_t /*first_array_index*/, uint32_t /*num_items*/, uint32_t /*first_level*/, uint32_t /*num_levels*/)
	{
		BOOST_ASSERT(false);
		static ID3D11ShaderResourceViewPtr ret;
		return ret;
	}

	ID3D11UnorderedAccessViewPtr const & D3D11Texture::RetriveD3DUnorderedAccessView(uint32_t /*first_array_index*/, uint32_t /*num_items*/, uint32_t /*level*/)
	{
		BOOST_ASSERT(false);
		static ID3D11UnorderedAccessViewPtr ret;
		return ret;
	}

	ID3D11UnorderedAccessViewPtr const & D3D11Texture::RetriveD3DUnorderedAccessView(uint32_t /*first_array_index*/, uint32_t /*num_items*/, CubeFaces /*first_face*/, uint32_t /*num_faces*/,
		uint32_t /*level*/)
	{
		BOOST_ASSERT(false);
		static ID3D11UnorderedAccessViewPtr ret;
		return ret;
	}

	ID3D11RenderTargetViewPtr const & D3D11Texture::RetriveD3DRenderTargetView(uint32_t /*first_array_index*/, uint32_t /*array_size*/, uint32_t /*level*/)
	{
		BOOST_ASSERT(false);
		static ID3D11RenderTargetViewPtr ret;
		return ret;
	}

	ID3D11RenderTargetViewPtr const & D3D11Texture::RetriveD3DRenderTargetView(uint32_t /*array_index*/, uint32_t /*first_slice*/, uint32_t /*num_slices*/, uint32_t /*level*/)
	{
		BOOST_ASSERT(false);
		static ID3D11RenderTargetViewPtr ret;
		return ret;
	}

	ID3D11RenderTargetViewPtr const & D3D11Texture::RetriveD3DRenderTargetView(uint32_t /*array_index*/, Texture::CubeFaces /*face*/, uint32_t /*level*/)
	{
		BOOST_ASSERT(false);
		static ID3D11RenderTargetViewPtr ret;
		return ret;
	}

	ID3D11DepthStencilViewPtr const & D3D11Texture::RetriveD3DDepthStencilView(uint32_t /*first_array_index*/, uint32_t /*array_size*/, uint32_t /*level*/)
	{
		BOOST_ASSERT(false);
		static ID3D11DepthStencilViewPtr ret;
		return ret;
	}

	ID3D11DepthStencilViewPtr const & D3D11Texture::RetriveD3DDepthStencilView(uint32_t /*array_index*/, uint32_t /*first_slice*/, uint32_t /*num_slices*/, uint32_t /*level*/)
	{
		BOOST_ASSERT(false);
		static ID3D11DepthStencilViewPtr ret;
		return ret;
	}

	ID3D11DepthStencilViewPtr const & D3D11Texture::RetriveD3DDepthStencilView(uint32_t /*array_index*/, Texture::CubeFaces /*face*/, uint32_t /*level*/)
	{
		BOOST_ASSERT(false);
		static ID3D11DepthStencilViewPtr ret;
		return ret;
	}

	void D3D11Texture::GetD3DFlags(D3D11_USAGE& usage, UINT& bind_flags, UINT& cpu_access_flags, UINT& misc_flags)
	{
		if (access_hint_ & EAH_Immutable)
		{
			usage = D3D11_USAGE_IMMUTABLE;
		}
		else
		{
			if ((EAH_CPU_Write | EAH_GPU_Read) == access_hint_)
			{
				usage = D3D11_USAGE_DYNAMIC;
			}
			else
			{
				if (EAH_CPU_Write == access_hint_)
				{
					if ((num_mip_maps_ != 1) || (TT_Cube == type_))
					{
						usage = D3D11_USAGE_STAGING;
					}
					else
					{
						usage = D3D11_USAGE_DYNAMIC;
					}
				}
				else
				{
					if (!(access_hint_ & EAH_CPU_Read) && !(access_hint_ & EAH_CPU_Write))
					{
						usage = D3D11_USAGE_DEFAULT;
					}
					else
					{
						usage = D3D11_USAGE_STAGING;
					}
				}
			}
		}

		bind_flags = 0;
		if ((access_hint_ & EAH_GPU_Read) || (D3D11_USAGE_DYNAMIC == usage))
		{
			bind_flags |= D3D11_BIND_SHADER_RESOURCE;
		}
		if (access_hint_ & EAH_GPU_Write)
		{
			if (IsDepthFormat(format_))
			{
				bind_flags |= D3D11_BIND_DEPTH_STENCIL;
			}
			else
			{
				bind_flags |= D3D11_BIND_RENDER_TARGET;
			}
		}
		if (access_hint_ & EAH_GPU_Unordered)
		{
			bind_flags |= D3D11_BIND_UNORDERED_ACCESS;
		}

		cpu_access_flags = 0;
		if (access_hint_ & EAH_CPU_Read)
		{
			cpu_access_flags |= D3D11_CPU_ACCESS_READ;
		}
		if (access_hint_ & EAH_CPU_Write)
		{
			cpu_access_flags |= D3D11_CPU_ACCESS_WRITE;
		}

		misc_flags = 0;
		if (access_hint_ & EAH_Generate_Mips)
		{
			misc_flags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;
		}
	}

	void D3D11Texture::CopyToSubTexture(Texture& target,
			uint32_t dst_sub_res, uint32_t dst_x_offset, uint32_t dst_y_offset, uint32_t dst_z_offset, uint32_t dst_width, uint32_t dst_height, uint32_t dst_depth,
			uint32_t src_sub_res, uint32_t src_x_offset, uint32_t src_y_offset, uint32_t src_z_offset, uint32_t src_width, uint32_t src_height, uint32_t src_depth)
	{
		D3D11Texture& other(*checked_cast<D3D11Texture*>(&target));

		if ((src_width == dst_width) && (src_height == dst_height) && (this->Format() == target.Format()))
		{
			D3D11_BOX src_box;
			src_box.left = src_x_offset;
			src_box.top = src_y_offset;
			src_box.front = src_z_offset;
			src_box.right = src_x_offset + src_width;
			src_box.bottom = src_y_offset + src_height;
			src_box.back = src_z_offset + src_depth;

			d3d_imm_ctx_->CopySubresourceRegion(other.D3DResource().get(), dst_sub_res,
				dst_x_offset, dst_y_offset, 0, this->D3DResource().get(), src_sub_res, &src_box);
		}
		else
		{
			D3D11_BOX src_box, dst_box;

			src_box.left = src_x_offset;
			src_box.top = src_y_offset;
			src_box.front = src_z_offset;
			src_box.right = src_x_offset + src_width;
			src_box.bottom = src_y_offset + src_height;
			src_box.back = src_z_offset + src_depth;

			dst_box.left = dst_x_offset;
			dst_box.top = dst_y_offset;
			dst_box.front = dst_z_offset;
			dst_box.right = dst_x_offset + dst_width;
			dst_box.bottom = dst_y_offset + dst_height;
			dst_box.back = dst_z_offset + dst_depth;

			D3DX11_TEXTURE_LOAD_INFO info;
			info.pSrcBox = &src_box;
			info.pDstBox = &dst_box;
			info.SrcFirstMip = src_sub_res;
			info.DstFirstMip = dst_sub_res;
			info.NumMips = 1;
			info.SrcFirstElement = 0;
			info.DstFirstElement = 0;
			info.NumElements = 0;
			info.Filter = D3DX11_FILTER_LINEAR;
			info.MipFilter = D3DX11_FILTER_LINEAR;
			if (IsSRGB(format_))
			{
				info.Filter |= D3DX11_FILTER_SRGB_IN;
				info.MipFilter |= D3DX11_FILTER_SRGB_IN;
			}
			if (IsSRGB(target.Format()))
			{
				info.Filter |= D3DX11_FILTER_SRGB_OUT;
				info.MipFilter |= D3DX11_FILTER_SRGB_OUT;
			}

			D3DX11LoadTextureFromTexture(d3d_imm_ctx_.get(), this->D3DResource().get(), &info, other.D3DResource().get());
		}
	}

	ID3D11ShaderResourceViewPtr const & D3D11Texture::RetriveD3DSRV(D3D11_SHADER_RESOURCE_VIEW_DESC const & desc)
	{
		char const * p = reinterpret_cast<char const *>(&desc);
		size_t hash_val;
		boost::hash_range(hash_val, p, p + sizeof(desc));

		BOOST_AUTO(iter, d3d_sr_views_.find(hash_val));
		if (iter != d3d_sr_views_.end())
		{
			return iter->second;
		}

		ID3D11ShaderResourceView* d3d_sr_view;
		d3d_device_->CreateShaderResourceView(this->D3DResource().get(), &desc, &d3d_sr_view);
		BOOST_AUTO(ret, d3d_sr_views_.insert(std::make_pair(hash_val, MakeCOMPtr(d3d_sr_view))));
		return ret.first->second;
	}

	ID3D11UnorderedAccessViewPtr const & D3D11Texture::RetriveD3DUAV(D3D11_UNORDERED_ACCESS_VIEW_DESC const & desc)
	{
		char const * p = reinterpret_cast<char const *>(&desc);
		size_t hash_val;
		boost::hash_range(hash_val, p, p + sizeof(desc));

		BOOST_AUTO(iter, d3d_ua_views_.find(hash_val));
		if (iter != d3d_ua_views_.end())
		{
			return iter->second;
		}

		ID3D11UnorderedAccessView* d3d_ua_view;
		d3d_device_->CreateUnorderedAccessView(this->D3DResource().get(), &desc, &d3d_ua_view);
		BOOST_AUTO(ret, d3d_ua_views_.insert(std::make_pair(hash_val, MakeCOMPtr(d3d_ua_view))));
		return ret.first->second;
	}

	ID3D11RenderTargetViewPtr const & D3D11Texture::RetriveD3DRTV(D3D11_RENDER_TARGET_VIEW_DESC const & desc)
	{
		char const * p = reinterpret_cast<char const *>(&desc);
		size_t hash_val;
		boost::hash_range(hash_val, p, p + sizeof(desc));

		BOOST_AUTO(iter, d3d_rt_views_.find(hash_val));
		if (iter != d3d_rt_views_.end())
		{
			return iter->second;
		}

		ID3D11RenderTargetView* rt_view;
		d3d_device_->CreateRenderTargetView(this->D3DResource().get(), &desc, &rt_view);
		BOOST_AUTO(ret, d3d_rt_views_.insert(std::make_pair(hash_val, MakeCOMPtr(rt_view))));
		return ret.first->second;
	}

	ID3D11DepthStencilViewPtr const & D3D11Texture::RetriveD3DDSV(D3D11_DEPTH_STENCIL_VIEW_DESC const & desc)
	{
		char const * p = reinterpret_cast<char const *>(&desc);
		size_t hash_val;
		boost::hash_range(hash_val, p, p + sizeof(desc));

		BOOST_AUTO(iter, d3d_ds_views_.find(hash_val));
		if (iter != d3d_ds_views_.end())
		{
			return iter->second;
		}

		ID3D11DepthStencilView* ds_view;
		d3d_device_->CreateDepthStencilView(this->D3DResource().get(), &desc, &ds_view);
		BOOST_AUTO(ret, d3d_ds_views_.insert(std::make_pair(hash_val, MakeCOMPtr(ds_view))));
		return ret.first->second;
	}

	void D3D11Texture::Map1D(uint32_t /*array_index*/, uint32_t /*level*/, TextureMapAccess /*tma*/,
			uint32_t /*x_offset*/, uint32_t /*width*/,
			void*& /*data*/)
	{
		BOOST_ASSERT(false);
	}

	void D3D11Texture::Map2D(uint32_t /*array_index*/, uint32_t /*level*/, TextureMapAccess /*tma*/,
			uint32_t /*x_offset*/, uint32_t /*y_offset*/, uint32_t /*width*/, uint32_t /*height*/,
			void*& /*data*/, uint32_t& /*row_pitch*/)
	{
		BOOST_ASSERT(false);
	}

	void D3D11Texture::Map3D(uint32_t /*array_index*/, uint32_t /*level*/, TextureMapAccess /*tma*/,
			uint32_t /*x_offset*/, uint32_t /*y_offset*/, uint32_t /*z_offset*/,
			uint32_t /*width*/, uint32_t /*height*/, uint32_t /*depth*/,
			void*& /*data*/, uint32_t& /*row_pitch*/, uint32_t& /*slice_pitch*/)
	{
		BOOST_ASSERT(false);
	}

	void D3D11Texture::MapCube(uint32_t /*array_index*/, CubeFaces /*face*/, uint32_t /*level*/, TextureMapAccess /*tma*/,
			uint32_t /*x_offset*/, uint32_t /*y_offset*/, uint32_t /*width*/, uint32_t /*height*/,
			void*& /*data*/, uint32_t& /*row_pitch*/)
	{
		BOOST_ASSERT(false);
	}

	void D3D11Texture::Unmap1D(uint32_t /*array_index*/, uint32_t /*level*/)
	{
		BOOST_ASSERT(false);
	}

	void D3D11Texture::Unmap2D(uint32_t /*array_index*/, uint32_t /*level*/)
	{
		BOOST_ASSERT(false);
	}

	void D3D11Texture::Unmap3D(uint32_t /*array_index*/, uint32_t /*level*/)
	{
		BOOST_ASSERT(false);
	}

	void D3D11Texture::UnmapCube(uint32_t /*array_index*/, CubeFaces /*face*/, uint32_t /*level*/)
	{
		BOOST_ASSERT(false);
	}
}
