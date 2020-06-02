#include "pch.h"
#include "Texture.h"

Texture::Texture()
{

}

void Texture::ReleaseTexture()
{
	m_texture->Release();
	m_texture = nullptr;
}

Texture::~Texture()
{
	m_texture->Release();
}

bool Texture::IntialiseTexture(ID3D11Device* device, std::wstring texturePath)
{
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	if (FAILED(DirectX::CreateWICTextureFromFile(device, texturePath.c_str(), resource.GetAddressOf(), &m_texture)))
	{
		return false;
	}
	textureName = texturePath;
	return true;
}
