#include "pch.h"
#include "RenderedObject.h"

RenderedObject::RenderedObject(Quad& quad, Texture& texture )
{
	m_renderQuad = &quad;
	std::vector<ID3D11ShaderResourceView*> base;
	base.push_back(texture.GetTexture());
	m_textures.push_back(base);
}
RenderedObject::RenderedObject(Quad& quad, std::vector<Texture*> animation)
{
	m_renderQuad = &quad;
	std::vector<ID3D11ShaderResourceView*> base;
	for (int i = 0; i < animation.size(); i++)
	{
		base.push_back(animation[i]->GetTexture());
	}
	m_textures.push_back(base);
}
void RenderedObject::UpdateMatrix(DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 scale, DirectX::XMFLOAT3 rotation)
{
	m_worldMatrix = DirectX::XMMatrixScaling(scale.x, scale.y, 1.0f) 
		* DirectX::XMMatrixRotationRollPitchYaw(rotation.x,rotation.y,rotation.z) 
		* DirectX::XMMatrixTranslation(position.x + scale.x / 2, position.y + scale.y / 2, position.z);
}

void RenderedObject::PushAnimationBack(std::vector<Texture*> animation)
{
	std::vector<ID3D11ShaderResourceView*> base;
	for (int i = 0; i < animation.size(); i++)
	{
		base.push_back(animation[i]->GetTexture());
	}
	m_textures.push_back(base);
}
