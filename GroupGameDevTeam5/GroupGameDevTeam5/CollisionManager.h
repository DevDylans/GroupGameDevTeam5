#pragma once
#include "ParticleModel.h"
#include <vector>

class CollisionManager
{
public:
	static CollisionManager* GetInstance()
	{
		return s_pInstance;
	}

	static void Create();
	static void Destroy();
	
	void EmptyVector() { _colliders.clear(); }
	void AddCollider(ParticleModel* collider) { _colliders.push_back(collider); }
	void RemoveCollider(int index) { _colliders.erase(_colliders.begin() + index); }

	ParticleModel* GetCollider(int index);

	void UpdatePhysics(float deltaTime);

	void CollisionDetection();
	void CollisionResolution(ParticleModel* object1, ParticleModel* object2);

private:
	std::vector<ParticleModel*> _colliders;
	
	void TopDownCollision(ParticleModel* object1, ParticleModel* object2);
	void SideWaysCollision(ParticleModel* object1, ParticleModel* object2);

protected:
	CollisionManager();

	static CollisionManager* s_pInstance;
};

