#pragma once
#include "Transform.h"

class ParticleModel
{
public:
	ParticleModel(Transform* transform);
	~ParticleModel();

	// Setters
	void SetVelocity(XMFLOAT3 newVelocity) { _velocity = newVelocity; }
	void SetVelocity(XMVECTOR newVelocity) { XMStoreFloat3(&_velocity, newVelocity); }

	void SetAcceleration(XMFLOAT3 newAcceleration) { _acceleration = newAcceleration; }
	void SetAcceleration(XMVECTOR newAcceleration) { XMStoreFloat3(&_acceleration, newAcceleration); }

	// Getters
	XMFLOAT3 GetVelocity() { return _velocity; }

	XMFLOAT3 GetAcceleration() { return _acceleration; }

	void ApplyForce(XMFLOAT3 force);
	void Update(float t);

private:
	Transform* _transform;

	XMFLOAT3 _velocity;
	XMFLOAT3 _acceleration;
	XMFLOAT3 _totalForce;

	void CalculateAcceleration(float delta);
	void CalculateVelocity(float delta);
	void CalculatePosition(float delta);
};

