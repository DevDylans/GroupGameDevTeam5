#pragma once
#include "Camera.h"
#include "RenderedObject.h"
#include "Quad.h"
#include "Shaders.h"
#include <vector>
class Graphics
{
public:
	Graphics(Microsoft::WRL::ComPtr<ID3D11Device>& device);
	void DefaultIntialize(Microsoft::WRL::ComPtr<ID3D11Device>& device);

	VertexShader* GetDefaultVertexShader() const { return m_vertexShaders[0]; }
	PixelShader* GetDefaultPixelShader() const { return m_pixelShaders[0]; }
	Quad* GetDefaultQuadType() const { return m_quadTypes[0]; }

	VertexShader* GetSpecificVertexShader(int id) const { return m_vertexShaders[id]; }
	PixelShader* GetSpecificPixelShader(int id) const { return m_pixelShaders[id]; }
	Quad* GetSpecificQuadType(int id) const { return m_quadTypes[id]; }

	std::vector<RenderedObject*> GetObjectsToRender() const { return m_objectsToRender; }
private:
	std::vector<VertexShader*> m_vertexShaders;
	std::vector<PixelShader*> m_pixelShaders;
	std::vector<Quad*> m_quadTypes;
	std::vector<RenderedObject*> m_objectsToRender;
};

