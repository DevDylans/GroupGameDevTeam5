#include "pch.h"
#include "ParticleModel.h"

ParticleModel::ParticleModel(Transform * transform) : _transform(transform)
{
	XMFLOAT3 initialValues = XMFLOAT3(0, 0, 0);

	_velocity = initialValues;
	_acceleration = initialValues;
	_totalForce = initialValues;
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

void ParticleModel::Update(float t)
{
	CalculateAcceleration(t);
	CalculateVelocity(t);
	CalculatePosition(t);

	_totalForce = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void ParticleModel::CalculateAcceleration(float delta)
{
	_acceleration.x += _totalForce.x * delta;
	_acceleration.y += _totalForce.y * delta;
	_acceleration.z += _totalForce.z * delta;
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