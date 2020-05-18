#include "pch.h"
#include "RenderedObject.h"

RenderedObject::RenderedObject(Quad& quad, Texture& texture )
{
	m_renderQuad = &quad;
	m_texture = texture.GetTexture();
	SetScale(10, 10);
	SetPosition(0, 0, 0);
	SetRotation(0, 0, 0);
}

RenderedObject::RenderedObject(Quad& quad, Texture& texture, float posX, float posY, float posZ)
{
	m_renderQuad = &quad;
	m_texture = texture.GetTexture();
	SetScale(10, 10);
	SetPosition(posX, posY, posZ);
	SetRotation(0, 0, 0);
}

RenderedObject::RenderedObject(Quad& quad, Texture& texture, float posX, float posY, float posZ, float scaleX, float scaleY)
{
	m_renderQuad = &quad;
	m_texture = texture.GetTexture();
	SetScale(scaleX, scaleY);
	SetPosition(posX, posY, posZ);
	SetRotation(0, 0, 0);
}

RenderedObject::RenderedObject(Quad& quad, Texture& texture, float posX, float posY, float posZ, float scaleX, float scaleY, float rotX, float rotY, float rotZ)
{
	m_renderQuad = &quad;
	m_texture = texture.GetTexture();
	SetScale(scaleX, scaleY);
	SetPosition(posX, posY, posZ);
	SetRotation(rotX, rotY, rotZ);
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
void RenderedObject::SetPosition(float x, float y, float z)
{
	m_position = DirectX::XMFLOAT3(x, y, z);
	m_positionVector = DirectX::XMLoadFloat3(&m_position);
	UpdateMatrix();
}
void RenderedObject::MovePosition(float x, float y, float z)
{
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;
	m_positionVector = DirectX::XMLoadFloat3(&m_position);
	UpdateMatrix();
}
void RenderedObject::MovePosition(const DirectX::XMVECTOR& pos)
{
	DirectX::XMVectorAdd(m_positionVector, pos);
	DirectX::XMStoreFloat3(&m_position, m_positionVector);
	UpdateMatrix();
}
void RenderedObject::SetRotation(float x, float y, float z)
{
	m_rotation = DirectX::XMFLOAT3(x, y, z);
	m_rotationVector = DirectX::XMLoadFloat3(&m_rotation);
	UpdateMatrix();
}
void RenderedObject::Rotate(float x, float y, float z)
{
	m_rotation.x += x;
	m_rotation.y += y;
	m_rotation.z += z;
	m_rotationVector = DirectX::XMLoadFloat3(&m_rotation);
	UpdateMatrix();
}
void RenderedObject::Rotate(DirectX::XMVECTOR& rot)
{
	DirectX::XMVectorAdd(m_rotationVector, rot);
	DirectX::XMStoreFloat3(&m_rotation, m_rotationVector);
	UpdateMatrix();
}
void RenderedObject::UpdateMatrix()
{
	m_worldMatrix = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, 1.0f) 
		* DirectX::XMMatrixRotationRollPitchYaw(m_rotation.x,m_rotation.y,m_rotation.z) 
		* DirectX::XMMatrixTranslation(m_position.x + m_scale.x / 2, m_position.y + m_scale.y / 2, m_position.z);
}
