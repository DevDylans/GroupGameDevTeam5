#pragma once
#include "pch.h"
#include <DirectXCollision.h>

using namespace DirectX;

struct BoxEntents
{
	float bottom;
	float top;
	float width;
	float height;

	BoxEntents(float BoxX, float BoxY, float BoxWidth, float BoxHeight)
	{
		bottom = BoxX;
		top = BoxY;
		width = BoxWidth;
		height = BoxHeight;
	}
};

class Collision
{
public:

	~Collision();
	static Collision* Instance();

	float collisionRadius;

	bool Circle(XMVECTOR character1, XMVECTOR character2);
	bool Box(BoxEntents collision1, BoxEntents collision2);

private:

	Collision();
	static Collision* cInstance;
};