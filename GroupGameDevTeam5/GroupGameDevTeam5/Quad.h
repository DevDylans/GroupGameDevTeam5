#pragma once
#include <DeviceResources.h>
#include <d3d11.h>

class Quad
{
public:
	Quad();
	ID3D11Buffer* GetVertexBuffer() { return m_vertexBuffer; }
	ID3D11Buffer* GetIndexBuffer()  { return m_indexBuffer; }
protected:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
};

