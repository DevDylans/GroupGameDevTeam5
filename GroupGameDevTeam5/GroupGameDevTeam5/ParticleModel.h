#pragma once
#include "Transform.h"
#include "CollisionComponent.h"

class ParticleModel
{
public:
	ParticleModel(Transform* transform, ColliderType type, XMFLOAT2 size);
	ParticleModel(Transform* transform, ColliderType type, XMFLOAT2 size, float mass, float accelerationG);
	~ParticleModel();

	// Setters
	void SetVelocity(XMFLOAT3 newVelocity) { _velocity = newVelocity; }
	void SetVelocity(XMVECTOR newVelocity) { XMStoreFloat3(&_velocity, newVelocity); }

	void SetAcceleration(XMFLOAT3 newAcceleration) { _acceleration = newAcceleration; }
	void SetAcceleration(XMVECTOR newAcceleration) { XMStoreFloat3(&_acceleration, newAcceleration); }

	void SetTransform(Transform* transform) { _transform = transform; }

	//void SetPhysicsSettings();

	void SetAccelerationG(float newG) { _accelerationG = newG; }
	void SetMass(float newMass) { _mass = newMass; }
	void SetCoeffR(float newR);

	// Getters
	XMFLOAT3 GetVelocity() { return _velocity; }

	XMFLOAT3 GetAcceleration() { return _acceleration; }

	Transform* GetTransform() { return _transform; }
	Transform GetOldTransform() { return _oldTransform; }
	CollisionComponent GetPhysicsComponent() { return _collisionRect; }

	float GetMass() { return _mass; }
	float GetAccelerationG() { return _accelerationG; }
	float GetCoeffR() { return _coeffR; }
	XMFLOAT3 GetTotalForce() { return _totalForce; }

	void ApplyForce(XMFLOAT3 force);
	void ApplyForce(XMVECTOR force);
	void SetForce(XMFLOAT3 force) { _totalForce = force; }
	void Update(float t);

private:
	Transform* _transform;
	Transform _oldTransform;
	CollisionComponent _collisionRect;

	float _mass = 1;
	float _accelerationG = 9.81;
	float _coeffR = 0.5;

	XMFLOAT3 _velocity;
	XMFLOAT3 _acceleration;
	XMFLOAT3 _totalForce;

	void CalculateAcceleration(float delta);
	void CalculateVelocity(float delta);
	void CalculatePosition(float delta);
};

