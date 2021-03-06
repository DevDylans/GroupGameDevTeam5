#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Transform
{
public:
	Transform();
	Transform(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT2 scale);
	~Transform();

	// Setters
	void SetPosition(XMFLOAT3 newPosition) { _position = newPosition; }
	void SetPosition(XMVECTOR newPosition) { XMStoreFloat3(&_position, newPosition); }
	void SetPosition(float x, float y, float z) { _position.x = x; _position.y = y; _position.z = z; }

	void SetRotation(XMFLOAT3 newRotation) { _rotation = newRotation; }
	void SetRotation(XMVECTOR newRotation) { XMStoreFloat3(&_rotation, newRotation); }
	void SetRotation(float x, float y, float z) { _rotation.x = x; _rotation.y = y; _rotation.z = z; }

	void SetScale(XMFLOAT2 newScale) { _scale = newScale; }
	void SetScale(XMVECTOR newScale) { XMStoreFloat2(&_scale, newScale); }
	void SetScale(float x, float y) { _scale.x = x; _scale.y = y; }

	// Getters
	XMFLOAT3 GetPosition() { return _position; }

	XMFLOAT3 GetRotation() { return _rotation; }

	XMFLOAT2 GetScale() { return _scale; }

private:
	XMFLOAT3 _position;
	XMFLOAT3 _rotation;
	XMFLOAT2 _scale;
};

