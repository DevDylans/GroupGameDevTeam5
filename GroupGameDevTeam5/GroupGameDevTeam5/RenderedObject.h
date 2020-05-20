#pragma once
#include "Quad.h"
#include <DirectXMath.h>
#include "Texture.h"
#include <vector>
class RenderedObject
{
public:
	RenderedObject(Quad& quad, Texture& texture);

	void Draw(ID3D11DeviceContext* context, DirectX::XMMATRIX orthoMatrix, DirectX::XMMATRIX cameraMatrix, Microsoft::WRL::ComPtr<ID3D11Buffer>& constantBuffer);

	DirectX::XMMATRIX GetWorldMatrix() { return m_worldMatrix; }
	Quad* GetQuad() const { return m_renderQuad; }
	ID3D11ShaderResourceView* GetTexture(int id) const { return m_textures[id]; }
	void UpdateMatrix(DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 scale, DirectX::XMFLOAT3 rotation);
private:


	DirectX::XMMATRIX m_worldMatrix = DirectX::XMMatrixIdentity();
	std::vector<ID3D11ShaderResourceView*> m_textures;

	Quad* m_renderQuad;
};

