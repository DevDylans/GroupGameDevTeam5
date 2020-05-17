#include "pch.h"
#include "Camera.h"

Camera::Camera()
{
	m_position = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	m_positionVector = XMLoadFloat3(&m_position);
	m_rotation = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	m_rotationVector = XMLoadFloat3(&m_rotation);
	UpdateMatrix();
}

void Camera::SetProjectionValues(float width, float height, float nearZ, float farZ)
{
	m_orthoMatrix = DirectX::XMMatrixOrthographicOffCenterLH(0.f, width, height, 0.f, nearZ, farZ);
}
void Camera::SetPosition(float x, float y, float z)
{
	m_position = DirectX::XMFLOAT3(x, y, z);
	m_positionVector = DirectX::XMLoadFloat3(&m_position);
	UpdateMatrix();
}
void Camera::MovePosition(float x, float y, float z)
{
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;
	m_positionVector = DirectX::XMLoadFloat3(&m_position);
	UpdateMatrix();
}
void Camera::MovePosition(const DirectX::XMVECTOR& pos)
{
	DirectX::XMVectorAdd(m_positionVector, pos);
	DirectX::XMStoreFloat3(&m_position, m_positionVector);
	UpdateMatrix();
}
void Camera::SetRotation(float x, float y, float z)
{
	m_rotation = DirectX::XMFLOAT3(x, y, z);
	m_rotationVector = DirectX::XMLoadFloat3(&m_rotation);
	UpdateMatrix();
}
void Camera::Rotate(float x, float y, float z)
{
	m_rotation.x += x;
	m_rotation.y += y;
	m_rotation.z += z;
	m_rotationVector = DirectX::XMLoadFloat3(&m_rotation);
	UpdateMatrix();
}
void Camera::Rotate(DirectX::XMVECTOR& rot)
{
	DirectX::XMVectorAdd(m_rotationVector, rot);
	DirectX::XMStoreFloat3(&m_rotation, m_rotationVector);
	UpdateMatrix();
}
void Camera::UpdateMatrix()
{
	DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(-m_position.x, -m_position.y, 0.f);
	DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
	m_worldMatrix = rotation * translation;
}
