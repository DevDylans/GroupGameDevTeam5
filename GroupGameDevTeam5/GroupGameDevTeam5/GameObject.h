#pragma once
using namespace DirectX;
#include "RenderedObject.h"
#include <Structs.h>
#include "ParticleModel.h"
#include "Collisions.h"
#include<algorithm>

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
	void MovePosition(float x, float y, float z);
	void MovePosition(const DirectX::XMVECTOR& pos);
	void SetRotation(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void Rotate(DirectX::XMVECTOR& pos);

	//void SetPhysicsComponent(ParticleModel* physicsModel) { physicsModel->SetTransform(&_objTransform); _particleModel = physicsModel; }

	void Update(float deltaTime);

	float GetCollisionRadius();
	BoxEntents GetCollisionBox();

	Transform GetTransform() { return _objTransform; }
private:
	XMVECTOR m_positionVector;
	XMVECTOR m_rotationVector;

	Transform _objTransform;
	RenderedObject* m_render = nullptr;
	ParticleModel* _particleModel = nullptr;
	float m_collisionRadius = 15;
};

