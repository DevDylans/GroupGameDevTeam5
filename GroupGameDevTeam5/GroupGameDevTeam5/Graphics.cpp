#include "pch.h"
#include "Graphics.h"

Graphics::Graphics(Microsoft::WRL::ComPtr<ID3D11Device>& device)
{
	DefaultIntialize(device);
}

void Graphics::DefaultIntialize(Microsoft::WRL::ComPtr<ID3D11Device>& device)
{
	D3D11_INPUT_ELEMENT_DESC texturedVertex[] =
	{
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
		{"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
	};
	UINT numElements = ARRAYSIZE(texturedVertex);
	VertexShader* vertexShader = new VertexShader();
	vertexShader->CreateShader(device, L"DefaultVertexShader.cso", texturedVertex, numElements);
	m_vertexShaders.push_back(vertexShader);
	PixelShader* pixShader = new PixelShader();
	pixShader->CreateShader(device, L"DefaultPixelShader.cso", texturedVertex, numElements);
	m_pixelShaders.push_back(pixShader);

}
