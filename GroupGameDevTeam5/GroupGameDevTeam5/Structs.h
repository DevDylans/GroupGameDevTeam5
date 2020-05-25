#pragma once
#include <DirectXMath.h>

struct TexturedVertex {
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 texCoord;
};
struct ConstantBuffer2D {
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX proj;
};

struct BoxEntents
{
	float x;
	float y;
	float width;
	float height;

	BoxEntents(float BoxX, float BoxY, float BoxWidth, float BoxHeight)
	{
		x = BoxX;
		y = BoxY;
		width = BoxWidth;
		height = BoxHeight;
	}
};
