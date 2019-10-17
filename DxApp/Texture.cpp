#include "Texture.h"
#include "DDSTextureLoader.h"

namespace wrl = Microsoft::WRL;

Texture::Texture(Graphics& gfx, const wchar_t* name)
{
	GFX_THROW_INFO(DirectX::CreateDDSTextureFromFile(GetDevice(gfx), name, nullptr, pTextureView.GetAddressOf()));
}

void Texture::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->PSSetShaderResources(0u, 1u, pTextureView.GetAddressOf());
}
