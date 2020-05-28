#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(float posX, float posY, float posZ)
{
	SetScale(10, 10);
	SetPosition(posX, posY, posZ);
	SetRotation(0, 0, 0);
}

GameObject::GameObject(XMFLOAT3 pos)
{
	SetScale(10, 10);
	SetPosition(pos.x, pos.y, pos.z);
	SetRotation(0, 0, 0);
}

GameObject::GameObject(float posX, float posY, float posZ, float scaleX, float scaleY)
{
	SetScale(scaleX, scaleY);
	SetPosition(posX, posY, posZ);
	SetRotation(0, 0, 0);
}

GameObject::GameObject(XMFLOAT3 pos, XMFLOAT2 scale)
{
	SetScale(scale.x, scale.y);
	SetPosition(pos.x, pos.y, pos.z);
	SetRotation(0, 0, 0);
}

GameObject::GameObject(float posX, float posY, float posZ, float scaleX, float scaleY, float rotX, float rotY, float rotZ)
{
	SetScale(scaleX, scaleY);
	SetPosition(posX, posY, posZ);
	SetRotation(rotX, rotY, rotZ);
}

GameObject::GameObject(XMFLOAT3 pos, XMFLOAT2 scale, XMFLOAT3 rotation)
{
	SetScale(scale.x, scale.y);
	SetPosition(pos.x, pos.y, pos.z);
	SetRotation(rotation.x, rotation.y, rotation.z);
}

void GameObject::SetRenderObject(RenderedObject* object)
{
	m_render = object;
	m_render->UpdateMatrix(m_position, m_scale, m_rotation);
}

void GameObject::SetScale(float x, float y)
{
	m_scale.x = x;
	m_scale.y = y;
	if (m_render != nullptr)
	{
		m_render->UpdateMatrix(m_position,m_scale,m_rotation);
	}
}

void GameObject::SetPosition(float x, float y, float z)
{
	m_position = DirectX::XMFLOAT3(x, y, z);
	m_positionVector = DirectX::XMLoadFloat3(&m_position);
	if (m_render != nullptr)
	{
		m_render->UpdateMatrix(m_position, m_scale, m_rotation);
	}
}
void GameObject::MovePosition(float x, float y, float z)
{
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;
	m_positionVector = DirectX::XMLoadFloat3(&m_position);
	if (m_render != nullptr)
	{
		m_render->UpdateMatrix(m_position, m_scale, m_rotation);
	}
}
void GameObject::MovePosition(const DirectX::XMVECTOR& pos)
{
	DirectX::XMVectorAdd(m_positionVector, pos);
	DirectX::XMStoreFloat3(&m_position, m_positionVector);
	if (m_render != nullptr)
	{
		m_render->UpdateMatrix(m_position, m_scale, m_rotation);
	}
}
void GameObject::SetRotation(float x, float y, float z)
{
	m_rotation = DirectX::XMFLOAT3(x, y, z);
	m_rotationVector = DirectX::XMLoadFloat3(&m_rotation);
	if (m_render != nullptr)
	{
		m_render->UpdateMatrix(m_position, m_scale, m_rotation);
	}
}
void GameObject::Rotate(float x, float y, float z)
{
	m_rotation.x += x;
	m_rotation.y += y;
	m_rotation.z += z;
	m_rotationVector = DirectX::XMLoadFloat3(&m_rotation);
	if (m_render != nullptr)
	{
		m_render->UpdateMatrix(m_position, m_scale, m_rotation);
	}
}
void GameObject::Rotate(DirectX::XMVECTOR& rot)
{
	DirectX::XMVectorAdd(m_rotationVector, rot);
	DirectX::XMStoreFloat3(&m_rotation, m_rotationVector);
	if (m_render != nullptr)
	{
		m_render->UpdateMatrix(m_position, m_scale, m_rotation);
	}
}

XMFLOAT3 GameObject::GetPosition()
{
	return m_position;
}

float GameObject::GetCollisionRadius()
{
	return m_collisionRadius;
}

BoxEntents GameObject::GetCollisionBox()
{
	return BoxEntents(m_position.x, m_position.y, m_scale.x, m_scale.y);
}
