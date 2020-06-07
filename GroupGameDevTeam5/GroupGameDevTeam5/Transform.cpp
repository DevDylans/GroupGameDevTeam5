#include "pch.h"
#include "Transform.h"

Transform::Transform()
{
}

Transform::Transform(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT2 scale)
Transform::Transform(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT2 scale) : _position(position), _rotation(rotation), _scale(scale)
{
}

Transform::Transform() : _position(XMFLOAT3(0, 0, 0)), _rotation(XMFLOAT3(0, 0, 0)), _scale(XMFLOAT2(0, 0))
{
}

Transform::~Transform()
{
}