#pragma once
#include "Quad.h"
#include <DirectXMath.h>
class TexturedQuad :
	public Quad
{
	struct TexturedVertex {
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 texCoord;
	};
public:
	TexturedQuad(Microsoft::WRL::ComPtr<ID3D11Device>& device);
private:
};

