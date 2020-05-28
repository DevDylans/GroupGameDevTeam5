#include "pch.h"
#include "Transform.h"

Transform::Transform()
{
}

Transform::Transform(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT2 scale)
{
	SetPosition(position);
	SetRotation(rotation);
	SetScale(scale);
}

Transform::~Transform()
{

}