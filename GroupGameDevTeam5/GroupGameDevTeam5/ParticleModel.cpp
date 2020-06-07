#include "pch.h"
#include "ParticleModel.h"

ParticleModel::ParticleModel(Transform * transform, ColliderType type, XMFLOAT2 size) : _transform(transform)
{
	XMFLOAT3 initialValues = XMFLOAT3(0, 0, 0);

	_velocity = initialValues;
	_acceleration = initialValues;
	_totalForce = initialValues;

	_collisionRect.type = type;
	_collisionRect.size.x = size.x + 50;
	_collisionRect.size.y = size.y + 50;
}

ParticleModel::ParticleModel(Transform* transform, ColliderType type, XMFLOAT2 size, float mass, float accelerationG) : _transform(transform)
{
	XMFLOAT3 initialValues = XMFLOAT3(0, 0, 0);

	_velocity = initialValues;
	_acceleration = initialValues;
	_totalForce = initialValues;

	_mass = mass;
	_accelerationG = accelerationG;

	_collisionRect.type = type;
	_collisionRect.size.x = size.x + 50;
	_collisionRect.size.y = size.y + 50;
}

ParticleModel::~ParticleModel()
{
}

void ParticleModel::ApplyForce(XMFLOAT3 force)
{
	_totalForce.x += force.x;
	_totalForce.y += force.y;
	_totalForce.z += force.z;
}

void ParticleModel::ApplyForce(XMVECTOR force)
{
	XMFLOAT3 forceToApply;
	XMStoreFloat3(&forceToApply, force);
	ApplyForce(forceToApply);
}

void ParticleModel::SetCoeffR(float newR)
{
	if (newR < 0.0)
	{
		_coeffR = 0;
	}
	else if (newR > 1.0)
	{
		_coeffR = 1;
	}
	else
	{
		_coeffR = newR;
	}
}

void ParticleModel::Update(float t)
{
	_oldTransform = *_transform;

	CalculateAcceleration(t);
	CalculateVelocity(t);
	CalculatePosition(t);

	_totalForce = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void ParticleModel::CalculateAcceleration(float delta)
{
	_acceleration.x = _totalForce.x * delta;
	_acceleration.y = _totalForce.y * delta;
	_acceleration.z = _totalForce.z * delta;
}

void ParticleModel::CalculateVelocity(float delta)
{
	_velocity.x += _acceleration.x * delta;
	_velocity.y += _acceleration.y * delta;
	_velocity.z += _acceleration.z * delta;
}

void ParticleModel::CalculatePosition(float delta)
{
	XMFLOAT3 currentPos = _transform->GetPosition();
	XMFLOAT3 newPos = XMFLOAT3(
		currentPos.x + _velocity.x * delta,
		currentPos.y + _velocity.y * delta,
		currentPos.z + _velocity.z * delta
	);

	_transform->SetPosition(newPos);
}