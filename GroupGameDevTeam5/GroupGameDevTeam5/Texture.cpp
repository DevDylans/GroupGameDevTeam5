#include "pch.h"
#include "Texture.h"

Texture::Texture(ID3D11Device* device, std::wstring texturePath)
{
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(DirectX::CreateWICTextureFromFile(device,texturePath.c_str(),resource.GetAddressOf(),&m_texture));
}
