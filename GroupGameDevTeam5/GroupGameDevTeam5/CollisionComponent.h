#pragma once

using namespace DirectX;

enum class ColliderType 
{
	Static,
	Kinematic,
	Trigger
};

struct CollisionComponent
{
	ColliderType type = ColliderType::Static;

	XMFLOAT2 size = XMFLOAT2(10, 10);
};
