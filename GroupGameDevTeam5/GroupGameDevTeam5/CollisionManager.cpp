#include "pch.h"
#include "CollisionManager.h"

CollisionManager* CollisionManager::s_pInstance = nullptr;

void CollisionManager::TopDownCollision(ParticleModel* object1, ParticleModel* object2)
{
	// Kinematic vs Static
	if (object1->GetPhysicsComponent().type == ColliderType::Static)
	{
		XMFLOAT3 objVel = object2->GetVelocity();
		objVel.y *= (-1 * object2->GetCoeffR());
		objVel.y += object1->GetVelocity().y;

		object2->GetTransform()->SetPosition(XMFLOAT3(object2->GetTransform()->GetPosition().x, object2->GetOldTransform().GetPosition().y, object2->GetTransform()->GetPosition().z));
		object2->ApplyForce(XMFLOAT3(0, -1 * object2->GetTotalForce().y, 0));
		object2->SetVelocity(objVel);
	}
	else if (object2->GetPhysicsComponent().type == ColliderType::Static)
	{
		XMFLOAT3 objVel = object1->GetVelocity();
		objVel.y *= (-1 * object1->GetCoeffR());
		objVel.y += object2->GetVelocity().y;

		object1->GetTransform()->SetPosition(XMFLOAT3(object1->GetTransform()->GetPosition().x, object1->GetOldTransform().GetPosition().y, object1->GetTransform()->GetPosition().z));
		object1->ApplyForce(XMFLOAT3(0, -1 * object1->GetTotalForce().y, 0));
		object1->SetVelocity(objVel);
	}
	// Kinematic vs Trigger
	else if (object1->GetPhysicsComponent().type == ColliderType::Trigger)
	{
		// Trigger Code
	}
	else if (object2->GetPhysicsComponent().type == ColliderType::Trigger)
	{
		// Trigger Code
	}
	// Kinematic vs Kinematic
	else
	{
		float m1v1 = object1->GetMass() * object1->GetVelocity().y;
		float m2v2 = object2->GetMass() * object2->GetVelocity().y;

		float m1COR = object1->GetMass() * object2->GetCoeffR();
		float m2COR = object2->GetMass() * object1->GetCoeffR();

		float newYVel1 = (m1v1 + m2v2 + m2COR * (object2->GetVelocity().y - object1->GetVelocity().y)) / (object1->GetMass() + object2->GetMass());
		float newYVel2 = (m1v1 + m2v2 + m1COR * (object1->GetVelocity().y - object2->GetVelocity().y)) / (object1->GetMass() + object2->GetMass());

		// v1 = (m1v1 + m2v2 + m2COR(v2 - v1)) / (m1 + m2)	---	On X axis only
		object1->GetTransform()->SetPosition(XMFLOAT3(object1->GetTransform()->GetPosition().x, object1->GetOldTransform().GetPosition().y, object1->GetTransform()->GetPosition().z));
		object1->ApplyForce(XMFLOAT3(0, -1 * object1->GetTotalForce().y, 0));
		object1->SetVelocity(XMFLOAT3(object1->GetVelocity().x, newYVel1, object1->GetVelocity().z));

		// v2 = (m1v1 + m2v2 + m1COR(v1 - v2)) / (m1 + m2)	--- On X axis only
		object2->GetTransform()->SetPosition(XMFLOAT3(object2->GetTransform()->GetPosition().x, object2->GetOldTransform().GetPosition().y, object2->GetTransform()->GetPosition().z));
		object2->ApplyForce(XMFLOAT3(0, -1 * object2->GetTotalForce().y, 0));
		object2->SetVelocity(XMFLOAT3(object2->GetVelocity().x, newYVel2, object2->GetVelocity().z));
	}
}

void CollisionManager::SideWaysCollision(ParticleModel* object1, ParticleModel* object2)
{
	// Kinematic vs Static
	if (object1->GetPhysicsComponent().type == ColliderType::Static)
	{
		XMFLOAT3 objVel = object2->GetVelocity();
		objVel.x *= (-1 * object2->GetCoeffR());
		objVel.x += object1->GetVelocity().x;

		object2->GetTransform()->SetPosition(XMFLOAT3(object2->GetOldTransform().GetPosition().x, object2->GetTransform()->GetPosition().y, object2->GetTransform()->GetPosition().z));
		object2->ApplyForce(XMFLOAT3(-1 * object2->GetTotalForce().x, 0, 0));
		object2->SetVelocity(objVel);
	}
	else if (object2->GetPhysicsComponent().type == ColliderType::Static)
	{
		XMFLOAT3 objVel = object1->GetVelocity();
		objVel.x *= (-1 * object1->GetCoeffR());
		objVel.x += object2->GetVelocity().x;

		object1->GetTransform()->SetPosition(XMFLOAT3(object1->GetOldTransform().GetPosition().x, object1->GetTransform()->GetPosition().y, object1->GetTransform()->GetPosition().z));
		object1->ApplyForce(XMFLOAT3(-1 * object1->GetTotalForce().x, 0, 0));
		object1->SetVelocity(objVel);
	}
	// Kinematic vs Trigger
	else if (object1->GetPhysicsComponent().type == ColliderType::Trigger)
	{
		// Trigger Code
	}
	else if (object2->GetPhysicsComponent().type == ColliderType::Trigger)
	{
		// Trigger Code
	}
	// Kinematic vs Kinematic
	else
	{
		float m1v1 = object1->GetMass() * object1->GetVelocity().x;
		float m2v2 = object2->GetMass() * object2->GetVelocity().x;

		float m1COR = object1->GetMass() * object2->GetCoeffR();
		float m2COR = object2->GetMass() * object1->GetCoeffR();

		float newXVel1 = (m1v1 + m2v2 + m2COR * (object2->GetVelocity().x - object1->GetVelocity().x)) / (object1->GetMass() + object2->GetMass());
		float newXVel2 = (m1v1 + m2v2 + m1COR * (object1->GetVelocity().x - object2->GetVelocity().x)) / (object1->GetMass() + object2->GetMass());

		// v1 = (m1v1 + m2v2 + m2COR(v2 - v1)) / (m1 + m2)	---	On X axis only
		object1->GetTransform()->SetPosition(XMFLOAT3(object1->GetOldTransform().GetPosition().x, object1->GetTransform()->GetPosition().y, object1->GetTransform()->GetPosition().z));
		object1->ApplyForce(XMFLOAT3(-1 * object1->GetTotalForce().x, 0, 0));
		object1->SetVelocity(XMFLOAT3(newXVel1, object1->GetVelocity().y, object1->GetVelocity().z));

		// v2 = (m1v1 + m2v2 + m1COR(v1 - v2)) / (m1 + m2)	--- On X axis only
		object2->GetTransform()->SetPosition(XMFLOAT3(object2->GetOldTransform().GetPosition().x, object2->GetTransform()->GetPosition().y, object2->GetTransform()->GetPosition().z));
		object2->ApplyForce(XMFLOAT3(-1 * object2->GetTotalForce().x, 0, 0));
		object2->SetVelocity(XMFLOAT3(newXVel2, object2->GetVelocity().y, object2->GetVelocity().z));
	}
}

CollisionManager::CollisionManager()
{}

void CollisionManager::CollisionDetection()
{
	if (_colliders.size() > 1)
	{
		for (std::vector<ParticleModel*>::size_type it = 0; it != _colliders.size() - 1; ++it)
		{
			for (std::vector<ParticleModel*>::size_type it2 = it + 1; !(it2 >= _colliders.size()); ++it2)
			{
				if (_colliders[it]->GetPhysicsComponent().type == ColliderType::Kinematic || _colliders[it2]->GetPhysicsComponent().type == ColliderType::Kinematic)
				{
					if (_colliders[it]->GetTransform()->GetPosition().x < _colliders[it2]->GetTransform()->GetPosition().x + _colliders[it2]->GetPhysicsComponent().size.x &&
						_colliders[it]->GetTransform()->GetPosition().x + _colliders[it]->GetPhysicsComponent().size.x > _colliders[it2]->GetTransform()->GetPosition().x &&
						_colliders[it]->GetTransform()->GetPosition().y < _colliders[it2]->GetTransform()->GetPosition().y + _colliders[it2]->GetPhysicsComponent().size.y &&
						_colliders[it]->GetTransform()->GetPosition().y + _colliders[it]->GetPhysicsComponent().size.y > _colliders[it2]->GetTransform()->GetPosition().y)
					{
						CollisionResolution(_colliders[it], _colliders[it2]);

						/*char szBuffer[1024];
						sprintf_s(szBuffer, "Collision\n");
						OutputDebugStringA(szBuffer);*/
					}
				}
			}
		}
	}
}

void CollisionManager::CollisionResolution(ParticleModel* object1, ParticleModel* object2)
{
	// Top-Down Collision
	if (object1->GetOldTransform().GetPosition().x < object2->GetOldTransform().GetPosition().x + object2->GetPhysicsComponent().size.x &&
		object1->GetOldTransform().GetPosition().x + object1->GetPhysicsComponent().size.x > object2->GetOldTransform().GetPosition().x)
	{
		TopDownCollision(object1, object2);
	}
	// SideWays Collision
	else if (object1->GetOldTransform().GetPosition().y < object2->GetOldTransform().GetPosition().y + object2->GetPhysicsComponent().size.y &&
			 object1->GetOldTransform().GetPosition().y + object1->GetPhysicsComponent().size.y > object2->GetOldTransform().GetPosition().y)
	{
		SideWaysCollision(object1, object2);
	}
	// Diagonal Collision
	else
	{
		TopDownCollision(object1, object2);
	}

	//object1->GetTransform()->SetPosition(object1->GetOldTransform().GetPosition());
	//object2->GetTransform()->SetPosition(object2->GetOldTransform().GetPosition());
}

void CollisionManager::UpdatePhysics(float deltaTime)
{
	for (std::vector<ParticleModel*>::size_type it = 0; it != _colliders.size(); ++it)
	{
		_colliders[it]->Update(deltaTime);
	}
}

void CollisionManager::Create()
{
	if (!s_pInstance)
	{
		s_pInstance = new CollisionManager();
	}
}

void CollisionManager::Destroy()
{
	delete s_pInstance;
	s_pInstance = nullptr;
}

ParticleModel* CollisionManager::GetCollider(int index)
{
	return _colliders[index];
}