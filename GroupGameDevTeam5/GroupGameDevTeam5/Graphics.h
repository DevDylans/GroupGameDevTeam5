#pragma once
#include "Camera.h"
#include "RenderedObject.h"
#include "Quad.h"
#include "TexturedQuad.h"
#include "Shaders.h"
#include "Structs.h"
#include "Texture.h"
#include <vector>

class Graphics
{
public:

	Graphics(ID3D11Device* device);
	void DefaultIntialize(ID3D11Device* device);
	void Draw(ID3D11DeviceContext* context);
	void Update(float time);

	VertexShader* GetDefaultVertexShader() const { return m_vertexShaders[0]; }
	PixelShader* GetDefaultPixelShader() const { return m_pixelShaders[0]; }
	Quad* GetDefaultQuadType() const { return m_quadTypes[0]; }

	VertexShader* GetSpecificVertexShader(int id) const { return m_vertexShaders[id]; }
	PixelShader* GetSpecificPixelShader(int id) const { return m_pixelShaders[id]; }
	Quad* GetSpecificQuadType(int id) const { return m_quadTypes[id]; }

	std::vector<RenderedObject*> GetObjectsToRender() const { return m_objectsToRender; }

	void CreateRenderObject(int quadID, int textureID);
	void CreateRenderObject(int quadID, int textureID,DirectX::XMFLOAT3 position);
	void CreateRenderObject(int quadID, int textureID, DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 scale);
	void CreateRenderObject(int quadID, int textureID, DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 scale, DirectX::XMFLOAT3 rotation);
private:
	std::vector<VertexShader*> m_vertexShaders;
	std::vector<PixelShader*> m_pixelShaders;
	std::vector<Quad*> m_quadTypes;
	std::vector<Texture*> m_textures;
	std::vector<RenderedObject*> m_objectsToRender;
	Camera* m_camera = nullptr;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState;
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_samplerState;
};

