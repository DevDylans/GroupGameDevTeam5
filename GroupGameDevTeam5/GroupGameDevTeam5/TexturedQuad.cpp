#include "pch.h"
#include "TexturedQuad.h"

TexturedQuad::TexturedQuad(ID3D11Device* device)
{
	TexturedVertex vertices[] =
	{
		{DirectX::XMFLOAT3(-1.f, 1.f, 0.5f), DirectX::XMFLOAT2(0.0f,0.0f)},
		{DirectX::XMFLOAT3(1.f, 1.f, 0.5f), DirectX::XMFLOAT2(1.0f,0.0f)},
		{DirectX::XMFLOAT3(-1.f, -1.f, 0.5f), DirectX::XMFLOAT2(0.0f,1.0f)},
		{DirectX::XMFLOAT3(1.f, -1.f, 0.5f), DirectX::XMFLOAT2(1.0f,1.0f)},
		//{DirectX::XMFLOAT3(-1.f, 1.f, 5.5f), DirectX::XMFLOAT2(0.0f,0.0f)},
		//{DirectX::XMFLOAT3(1.f, 1.f, 5.5f), DirectX::XMFLOAT2(1.0f,0.0f)},
		//{DirectX::XMFLOAT3(-1.f, -1.f, 5.5f), DirectX::XMFLOAT2(0.0f,1.0f)},
		//{DirectX::XMFLOAT3(1.f, -1.f, 5.5f), DirectX::XMFLOAT2(1.0f,1.0f)}

	};
	UINT indices[] = {
	0, 1, 2,    // side 1
	2, 1, 3,
	//4, 0, 6,    // side 2
	//6, 0, 2,
	//7, 5, 6,    // side 3
	//6, 5, 4,
	//3, 1, 7,    // side 4
	//7, 1, 5,
	//4, 5, 0,    // side 5
	//0, 5, 1,
	//3, 7, 2,    // side 6
	//2, 7, 6,
	};
	CD3D11_BUFFER_DESC vertexDesc;
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.ByteWidth = sizeof(TexturedVertex) * 4;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.CPUAccessFlags = 0;
	vertexDesc.MiscFlags = 0;
	vertexDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;

	CD3D11_BUFFER_DESC indexDesc;
	indexDesc.Usage = D3D11_USAGE_DEFAULT;
	indexDesc.ByteWidth = sizeof(UINT) * 6;
	indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexDesc.CPUAccessFlags = 0;
	indexDesc.MiscFlags = 0;
	indexDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;

	DX::ThrowIfFailed(device->CreateBuffer(&vertexDesc, &vertexData, &m_vertexBuffer));
	DX::ThrowIfFailed(device->CreateBuffer(&indexDesc, &indexData, &m_indexBuffer));
}
