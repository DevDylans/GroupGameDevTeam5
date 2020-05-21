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