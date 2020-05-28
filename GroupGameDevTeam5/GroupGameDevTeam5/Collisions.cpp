#include "pch.h"
#include "Collisions.h"

Collision* Collision::cInstance = NULL;

Collision::Collision()
{
	
}

Collision::~Collision()
{
	cInstance = NULL;
}

Collision* Collision::Instance()
{
	if (!cInstance)
	{
		cInstance = new Collision;
	}
	return cInstance;
}

bool Collision::Circle(GameObject * Object1, GameObject * Object2)
{
	XMFLOAT3 location = XMFLOAT3((Object1->GetTransform().GetPosition().x - Object1->GetTransform().GetPosition().x),(Object1->GetTransform().GetPosition().y - Object2->GetTransform().GetPosition().y), 0.0f);
	double distance = sqrt((location.x*location.x) + (location.y*location.y));
	double combinedDistance = (Object1->GetCollisionRadius() + Object2->GetCollisionRadius());

	return distance < combinedDistance;
}

bool Collision::Box(BoxEntents collision1, BoxEntents collision2)
{
	if (collision1.x + (collision1.width / 2) > collision2.x && collision1.x + (collision1.width / 2) < collision2.x + collision2.width &&
		collision1.y + (collision1.height / 2) > collision2.y && collision1.y + (collision1.height / 2) < collision2.y + collision2.height)
	{
		return true;
	}
	return false;
}