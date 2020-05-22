#pragma once
#include "packages\directxtk_desktop_2015.2019.12.17.1\include\WICTextureLoader.h"
class Texture
{
public:
	Texture(ID3D11Device* device, std::wstring texturePath);
	ID3D11ShaderResourceView* GetTexture() { return m_texture; }
private:
	ID3D11ShaderResourceView* m_texture;
};
