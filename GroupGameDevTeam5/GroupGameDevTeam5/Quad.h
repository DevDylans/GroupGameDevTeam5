#pragma once
#include <DeviceResources.h>
#include <d3d11.h>

class Quad
{
public:
	Quad();
	ID3D11Buffer* GetVertexBuffer() const { return m_vertexBuffer; }
	ID3D11Buffer* GetIndexBuffer() const { return m_indexBuffer; }
	ID3D11InputLayout* GetInputLayout() const { return m_inputLayout; }
protected:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	ID3D11InputLayout* m_inputLayout = nullptr;
};

