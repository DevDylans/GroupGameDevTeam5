#pragma once
#include "Camera.h"
#include "RenderedObject.h"
#include "Quad.h"
#include "TexturedQuad.h"
#include "Shaders.h"
#include "Structs.h"
#include "Texture.h"
#include "GameObject.h"
#include <vector>

class Graphics
{
public:
	Graphics(ID3D11Device* device);
	void DefaultIntialize(ID3D11Device* device);
	void Draw(ID3D11DeviceContext* context, int shaderID, GameObject* object);
	void Draw(ID3D11DeviceContext* context, int shaderID, std::vector<GameObject*> objects);
	void Update(float time);
	void ChangeCameraProjection(float, float, float, float);

	VertexShader* GetSpecificVertexShader(int id) const { return m_vertexShaders[id]; }
	PixelShader* GetSpecificPixelShader(int id) const { return m_pixelShaders[id]; }
	Quad* GetSpecificQuadType(int id) const { return m_quadTypes[id]; }

	std::vector<RenderedObject*> GetObjectsToRender() const { return m_objectsToRender; }
	RenderedObject* GetSpecificRenderObject(int id);

	std::string CreateRenderObject(int quadID, int textureID);
	std::string CreateAnimatedRenderObject(int quadID, int animationID, float frameTime);

	Texture* GetSpecificAnimation(int animID, int frame);
	int GetNumberOfFrames(int animID);
	std::string CreateTexture(ID3D11Device* device, std::wstring texturePath);
	std::string CreateTextureGroup(ID3D11Device* device, std::vector<std::wstring> texturePath);
	std::string DeleteTexture(int texID);

	std::string AddAnimationToRenderObject(int objectID, int animationID, float frameTime);
	void AddAnimationToRenderObject(RenderedObject* object, int animationID, float frameTime);
	std::string RemoveAnimationFromRenderObject(int objectID, int animationID);
	std::string DeleteRenderedObject(int objID);
private:
	std::vector<VertexShader*> m_vertexShaders;
	std::vector<PixelShader*> m_pixelShaders;
	std::vector<Quad*> m_quadTypes;
	std::vector<std::vector<Texture*>> m_animations;
	std::vector<RenderedObject*> m_objectsToRender;
	Camera* m_camera = nullptr;

	ID3D11BlendState* m_blendState;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_samplerState;
};

