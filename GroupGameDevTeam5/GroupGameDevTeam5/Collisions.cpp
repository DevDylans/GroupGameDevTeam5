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
	XMFLOAT3 location = XMFLOAT3((Object1->GetPosition().x - Object1->GetPosition().x),(Object1->GetPosition().y - Object2->GetPosition().y), 0.0f);
	double distance = sqrt((location.x*location.x) + (location.y*location.y));
	double combinedDistance = (Object1->GetCollisionRadius() + Object2->GetCollisionRadius());

	return distance < combinedDistance;
}

bool Collision::Box(BoxEntents collision1, BoxEntents collision2)
{
	if (collision1.bottom + (collision1.width / 2) > collision2.bottom && collision1.bottom + (collision1.width / 2) < collision2.bottom + collision2.width &&
		collision1.top + (collision1.height / 2) > collision2.top && collision1.top + (collision1.height / 2) < collision2.top + collision2.height)
	{
		return true;
	}
	return false;
}