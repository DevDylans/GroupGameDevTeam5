#pragma once
#include "Quad.h"
#include <DirectXMath.h>
#include "Texture.h"
#include <vector>
class RenderedObject
{
public:
	RenderedObject(Quad& quad, Texture& texture);

	DirectX::XMMATRIX GetWorldMatrix() { return m_worldMatrix; }
	Quad* GetQuad() const { return m_renderQuad; }
	ID3D11ShaderResourceView* GetTexture(int id,int frameID) const { return m_textures[id][frameID]; }

	void UpdateMatrix(DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 scale, DirectX::XMFLOAT3 rotation);

private:
	DirectX::XMMATRIX m_worldMatrix = DirectX::XMMatrixIdentity();
	std::vector<std::vector<ID3D11ShaderResourceView*>> m_textures;
	Quad* m_renderQuad;
};

