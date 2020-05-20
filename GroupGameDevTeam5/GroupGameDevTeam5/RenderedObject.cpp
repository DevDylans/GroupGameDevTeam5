#include "pch.h"
#include "RenderedObject.h"

RenderedObject::RenderedObject(Quad& quad, Texture& texture )
{
	m_renderQuad = &quad;
	m_textures.push_back(texture.GetTexture());
}
void RenderedObject::Draw(ID3D11DeviceContext* context, DirectX::XMMATRIX orthoMatrix, DirectX::XMMATRIX cameraMatrix, Microsoft::WRL::ComPtr<ID3D11Buffer>& constantBuffer)
{
	//ConstantBuffer2D cb;
	//DirectX::XMMATRIX wvpMatrix = m_worldMatrix * orthoMatrix * cameraMatrix;
	//cb.wvpMatrix = DirectX::XMMatrixTranspose(wvpMatrix);
	//context->UpdateSubresource(constantBuffer.Get(), 0, nullptr, &cb,0,0);
	//context->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
	//context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());
}
void RenderedObject::UpdateMatrix(DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 scale, DirectX::XMFLOAT3 rotation)
{
	m_worldMatrix = DirectX::XMMatrixScaling(scale.x, scale.y, 1.0f) 
		* DirectX::XMMatrixRotationRollPitchYaw(rotation.x,rotation.y,rotation.z) 
		* DirectX::XMMatrixTranslation(position.x + scale.x / 2, position.y + scale.y / 2, position.z);
}
