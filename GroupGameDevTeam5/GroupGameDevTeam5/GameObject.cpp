#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(float posX, float posY, float posZ)
{
	XMFLOAT3 pos = XMFLOAT3(posX, posY, posZ);
	XMFLOAT3 rot = XMFLOAT3(0, 0, 0);
	XMFLOAT2 scale = XMFLOAT2(10, 10);

	_objTransform = Transform(pos, rot, scale);
	m_positionVector = XMLoadFloat3(&pos);
	m_rotationVector = XMLoadFloat3(&rot);
}

GameObject::GameObject(XMFLOAT3 pos)
{
	XMFLOAT3 rot = XMFLOAT3(0, 0, 0);
	XMFLOAT2 scale = XMFLOAT2(10, 10);

	_objTransform = Transform(pos, rot, scale);
	m_positionVector = XMLoadFloat3(&pos);
	m_rotationVector = XMLoadFloat3(&rot);
}

GameObject::GameObject(float posX, float posY, float posZ, float scaleX, float scaleY)
{
	XMFLOAT3 pos = XMFLOAT3(posX, posY, posZ);
	XMFLOAT3 rot = XMFLOAT3(0, 0, 0);
	XMFLOAT2 scale = XMFLOAT2(scaleX, scaleY);

	_objTransform = Transform(pos, rot, scale);
	m_positionVector = XMLoadFloat3(&pos);
	m_rotationVector = XMLoadFloat3(&rot);
}

GameObject::GameObject(XMFLOAT3 pos, XMFLOAT2 scale)
{
	XMFLOAT3 rot = XMFLOAT3(0, 0, 0);

	_objTransform = Transform(pos, rot, scale);
	m_positionVector = XMLoadFloat3(&pos);
	m_rotationVector = XMLoadFloat3(&rot);
}

GameObject::GameObject(float posX, float posY, float posZ, float scaleX, float scaleY, float rotX, float rotY, float rotZ)
{
	XMFLOAT3 pos = XMFLOAT3(posX, posY, posZ);
	XMFLOAT3 rot = XMFLOAT3(rotX, rotY, rotZ);
	XMFLOAT2 scale = XMFLOAT2(scaleX, scaleY);

	_objTransform = Transform(pos, rot, scale);
	m_positionVector = XMLoadFloat3(&pos);
	m_rotationVector = XMLoadFloat3(&rot);
}

GameObject::GameObject(XMFLOAT3 pos, XMFLOAT2 scale, XMFLOAT3 rotation)
{
	_objTransform = Transform(pos, rotation, scale);
	m_positionVector = XMLoadFloat3(&pos);
	m_rotationVector = XMLoadFloat3(&rotation);
}

void GameObject::SetRenderObject(RenderedObject* object)
{
	m_render = object;
	m_render->UpdateMatrix(_objTransform.GetPosition(), _objTransform.GetScale(), _objTransform.GetRotation());
}

void GameObject::SetScale(float x, float y)
{
	_objTransform.SetScale(x, y);

	if (m_render != nullptr)
	{
		m_render->UpdateMatrix(_objTransform.GetPosition(), _objTransform.GetScale(), _objTransform.GetRotation());
	}
}

void GameObject::SetPosition(float x, float y, float z)
{
	XMFLOAT3 _newPos = XMFLOAT3(x, y, z);
	_objTransform.SetPosition(_newPos);

	m_positionVector = XMLoadFloat3(&_newPos);
	if (m_render != nullptr)
	{
		m_render->UpdateMatrix(_objTransform.GetPosition(), _objTransform.GetScale(), _objTransform.GetRotation());
	}
}

void GameObject::SetRotation(float x, float y, float z)
{
	XMFLOAT3 _newRot = XMFLOAT3(x, y, z);
	_objTransform.SetRotation(_newRot);

	m_rotationVector = XMLoadFloat3(&_newRot);
	if (m_render != nullptr)
	{
		m_render->UpdateMatrix(_objTransform.GetPosition(), _objTransform.GetScale(), _objTransform.GetRotation());
	}
}


void GameObject::MovePosition(float x, float y, float z)
{
	XMFLOAT3 _currPos = _objTransform.GetPosition();
	_currPos.x += x;
	_currPos.y += y;
	_currPos.z += z;
	_objTransform.SetPosition(_currPos);

	m_positionVector = DirectX::XMLoadFloat3(&_currPos);
	if (m_render != nullptr)
	{
		m_render->UpdateMatrix(_objTransform.GetPosition(), _objTransform.GetScale(), _objTransform.GetRotation());
	}
}

void GameObject::MovePosition(const DirectX::XMVECTOR& pos)
{
	XMFLOAT3 position;
	XMStoreFloat3(&position, pos);
	MovePosition(position.x, position.y, position.z);
}

void GameObject::Rotate(float x, float y, float z)
{
	XMFLOAT3 _currRot = _objTransform.GetRotation();
	_currRot.x += x;
	_currRot.y += y;
	_currRot.z += z;
	_objTransform.SetRotation(_currRot);

	m_rotationVector = DirectX::XMLoadFloat3(&_currRot);
	if (m_render != nullptr)
	{
		m_render->UpdateMatrix(_objTransform.GetPosition(), _objTransform.GetScale(), _objTransform.GetRotation());
	}
}

void GameObject::Rotate(DirectX::XMVECTOR& rot)
{
	XMFLOAT3 rotation;
	XMStoreFloat3(&rotation, rot);
	Rotate(rotation.x, rotation.y, rotation.z);
}

void GameObject::Update(float deltaTime)
{

}
