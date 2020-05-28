#include "pch.h"
#include "Camera.h"
using namespace DirectX;
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
	m_orthoMatrix = DirectX::XMMatrixOrthographicOffCenterLH(0.f, width, 0.f, height, nearZ, farZ);
	UpdateMatrix();
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
	m_positionVector += pos;
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
	m_positionVector += rot;
	DirectX::XMStoreFloat3(&m_rotation, m_rotationVector);
	UpdateMatrix();
}
void Camera::UpdateMatrix()
{	
	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
	XMVECTOR camTarget = XMVector3TransformCoord(m_defaultForward, camRotationMatrix);
	camTarget += m_positionVector;
	XMVECTOR up = XMVector3TransformCoord(m_camUp, camRotationMatrix);
	m_viewMatrix = XMMatrixLookAtLH(m_positionVector, camTarget, up);
	
	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f,m_rotation.y,0.0f);
	m_camForwad = XMVector3TransformCoord(m_defaultForward, vecRotationMatrix);
	m_camBack = XMVector3TransformCoord(m_defaultBack, vecRotationMatrix);
	m_camLeft = XMVector3TransformCoord(m_defaultLeft, vecRotationMatrix);
	m_camRight = XMVector3TransformCoord(m_defaultRight, vecRotationMatrix);
}
