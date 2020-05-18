#pragma once

class Texture
{
public:
	Texture(ID3D11Device* device, std::wstring texturePath);
	ID3D11ShaderResourceView* GetTexture() { return m_texture; }
private:
	ID3D11ShaderResourceView* m_texture;
};

