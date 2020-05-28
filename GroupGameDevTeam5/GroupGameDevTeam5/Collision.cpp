#include "Collision.h"

Collision* Collision::cInstance = NULL;

Collision::Collision()
{
	collisionRadius = 15;
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

bool Collision::Circle(XMVECTOR position1, XMVECTOR position2)
{
	XMVECTOR vec = XMVECTOR(position1 - position2)(position1 - position2);
	double distance = sqrt((vec.x*vec.x) + (vec.y*vec.y));
	double combinedDistance = (collisionRadius + collisionRadius);

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