#pragma once
#include "pch.h"
#include "Structs.h"
#include "GameObject.h"
#include <DirectXCollision.h>

using namespace DirectX;
class GameObject;

class Collision
{
public:

	~Collision();
	static Collision* Instance();

	bool Circle(GameObject* Object1, GameObject* Object2);
	bool Box(BoxEntents collision1, BoxEntents collision2);

private:

	Collision();
	static Collision* cInstance;
};