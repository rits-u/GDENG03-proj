#include "Texture.h"
#include <DirectXTex.h>
#include "GraphicsEngine.h"

Texture::Texture(const wchar_t* fullPath) : Resource(fullPath)
{
	DirectX::ScratchImage imageData;
	HRESULT res = DirectX::LoadFromWICFile(fullPath, DirectX::WIC_FLAGS_NONE, nullptr, imageData);

	if (SUCCEEDED(res)) {
		res = DirectX::CreateTexture(GraphicsEngine::get()->getRenderSystem()->m_d3d_device,
			imageData.GetImages(), imageData.GetImageCount(), imageData.GetMetadata(), &this->texture);


		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = imageData.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = imageData.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		GraphicsEngine::get()->getRenderSystem()->m_d3d_device->CreateShaderResourceView(this->texture, &desc, &this->shaderResourceView);
	}
	else {
		throw std::exception("Texture not created successfully"); 
	}
}

Texture::~Texture()
{
	this->texture->Release();
}
