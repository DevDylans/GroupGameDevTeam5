#pragma once
using namespace DirectX;
#include "RenderedObject.h"
#include "ParticleModel.h"

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
	void UpdateRenderMatrix() { m_render->UpdateMatrix(_objTransform.GetPosition(), _objTransform.GetScale(), _objTransform.GetRotation()); }

	void SetScale(float x, float y);
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetPhysicsComponent(ParticleModel* physicsModel) { physicsModel->SetTransform(&_objTransform); _particleModel = physicsModel; }

	void MovePosition(float x, float y, float z);
	void MovePosition(const DirectX::XMVECTOR& pos);
	
	void Rotate(float x, float y, float z);
	void Rotate(DirectX::XMVECTOR& pos);

	void Update(float deltaTime);

	Transform GetTransform() { return _objTransform; }
	Transform* GetTransformP() { return &_objTransform; }
	ParticleModel* GetPhysicsComponent() { return _particleModel; }

private:
	Transform _objTransform;
	XMVECTOR m_positionVector = XMVectorZero();
	XMVECTOR m_rotationVector = XMVectorZero();

	ParticleModel* _particleModel = nullptr;

	RenderedObject* m_render = nullptr;
};

