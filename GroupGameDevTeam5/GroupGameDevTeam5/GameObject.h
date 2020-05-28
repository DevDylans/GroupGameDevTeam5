#pragma once
using namespace DirectX;
#include "RenderedObject.h"

class GameObject
{
public:
	GameObject(float posX, float posY, float posZ);
	GameObject(XMFLOAT3 pos);
	GameObject(float posX, float posY, float posZ, float scaleX, float scaleY);
	GameObject(XMFLOAT3 pos, XMFLOAT2 scale);
	GameObject(float posX, float posY, float posZ, float scaleX, float scaleY, float rotX, float rotY, float rotZ);
	GameObject(XMFLOAT3 pos, XMFLOAT2 scale, XMFLOAT3 rotation);

	void SetRenderObject(RenderedObject* object);
	RenderedObject* GetRenderObject() { return m_render; }
	void UpdateRenderMatrix() { m_render->UpdateMatrix(m_position, m_scale, m_rotation); }

	void SetScale(float x, float y);
	void SetPosition(float x, float y, float z);
	void MovePosition(float x, float y, float z);
	void MovePosition(const DirectX::XMVECTOR& pos);
	void SetRotation(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void Rotate(DirectX::XMVECTOR& pos);

	XMFLOAT3 GetPosition() { return m_position; }
	XMFLOAT2 GetScale() { return m_scale; }
	XMFLOAT3 GetRotation() { return m_rotation; }
private:
	XMFLOAT2 m_scale;
	XMFLOAT3 m_rotation;
	XMFLOAT3 m_position;
	XMVECTOR m_positionVector;
	XMVECTOR m_rotationVector;

	RenderedObject* m_render = nullptr;
};

