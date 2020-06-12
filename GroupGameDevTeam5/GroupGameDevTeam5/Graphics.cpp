#include "pch.h"
#include "Graphics.h"
using namespace DirectX;
Graphics::Graphics(ID3D11Device* device)
{
	DefaultIntialize(device);
}

void Graphics::DefaultIntialize(ID3D11Device* device)
{
	D3D11_INPUT_ELEMENT_DESC texturedVertex[] =
	{
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
		{"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
	};
	UINT numElements = ARRAYSIZE(texturedVertex);
	VertexShader* vertexShader = new VertexShader();
	vertexShader->CreateShader(device, L"DefaultVertexShader.hlsl", texturedVertex, numElements);
	m_vertexShaders.push_back(vertexShader);
	PixelShader* pixShader = new PixelShader();
	pixShader->CreateShader(device, L"DefaultPixelShader.hlsl", texturedVertex, numElements);
	m_pixelShaders.push_back(pixShader);
	Quad* newQuad = new TexturedQuad(device);
	m_quadTypes.push_back(newQuad);
	m_camera = new Camera();
	m_camera->SetPosition(0, 0, 0);
	m_camera->SetProjectionValues(1600, 900, 0.1, 50);

	CreateTexture(device, L"Transparent.png");
	CreateRenderObject(0, 0);

	CD3D11_RASTERIZER_DESC rastDesc(D3D11_DEFAULT);
	//rastDesc.CullMode = D3D11_CULL_NONE;

	DX::ThrowIfFailed(device->CreateRasterizerState(&rastDesc, m_rasterizerState.GetAddressOf()));

	CD3D11_SAMPLER_DESC sampDesc(D3D11_DEFAULT);
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	DX::ThrowIfFailed(device->CreateSamplerState(&sampDesc, m_samplerState.GetAddressOf()));

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer2D);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	DX::ThrowIfFailed(device->CreateBuffer(&bd, nullptr, &m_constantBuffer));

	CD3D11_BLEND_DESC blendDesc = {};
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	DX::ThrowIfFailed(device->CreateBlendState(&blendDesc, &m_blendState));

	//setup ImGui

}

//call from inside gameloop
void Graphics::Draw(ID3D11DeviceContext* context, int shaderID, GameObject* object)
{
	UINT stride = sizeof(TexturedVertex);
	UINT offset = 0;
	ConstantBuffer2D cb;

	context->OMSetBlendState(m_blendState, nullptr, 0xffffffff);
	context->IASetInputLayout(m_vertexShaders[shaderID]->GetInputLayout());
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->RSSetState(m_rasterizerState.Get());
	context->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
	context->VSSetShader(m_vertexShaders[shaderID]->GetShader(), NULL, 0);
	context->PSSetShader(m_pixelShaders[shaderID]->GetShader(), NULL, 0);

	cb.view = XMMatrixTranspose(m_camera->GetViewMatrix());
	cb.proj = XMMatrixTranspose(m_camera->GetOrthoMatrix());

	ID3D11Buffer* vb = object->GetRenderObject()->GetQuad()->GetVertexBuffer();
	context->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
	context->IASetIndexBuffer(object->GetRenderObject()->GetQuad()->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	int frame = object->GetRenderObject()->GetCurrentFrame();
	int anim = object->GetRenderObject()->GetCurrentAnimation();
	ID3D11ShaderResourceView* currentTex = object->GetRenderObject()->GetTexture(anim, frame);
	context->PSSetShaderResources(0, 1, &currentTex);
	object->UpdateRenderMatrix();
	cb.world = XMMatrixTranspose(object->GetRenderObject()->GetWorldMatrix());
	context->UpdateSubresource(m_constantBuffer.Get(), 0, nullptr, &cb, 0, 0);
	context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
	context->DrawIndexed(6, 0, 0);
}

void Graphics::Draw(ID3D11DeviceContext* context, int shaderID, std::vector<GameObject*> objects)
{
	UINT stride = sizeof(TexturedVertex);
	UINT offset = 0;
	Quad* currentQuad = nullptr;
	ID3D11ShaderResourceView* currentTex = nullptr;
	RenderedObject* currentRenderObj = nullptr;
	ConstantBuffer2D cb;

	context->OMSetBlendState(m_blendState, nullptr, 0xffffffff);
	context->IASetInputLayout(m_vertexShaders[shaderID]->GetInputLayout());
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->RSSetState(m_rasterizerState.Get());
	context->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
	context->VSSetShader(m_vertexShaders[shaderID]->GetShader(), NULL, 0);
	context->PSSetShader(m_pixelShaders[shaderID]->GetShader(), NULL, 0);
	cb.view = XMMatrixTranspose(m_camera->GetViewMatrix());
	cb.proj = XMMatrixTranspose(m_camera->GetOrthoMatrix());
	int size = objects.size();
	for (int i = 0; i < size; i++)
	{
		if (objects[i]->GetRenderObject() != nullptr)
		{
			if (objects[i]->GetRenderObject() != currentRenderObj)
			{
				currentRenderObj = objects[i]->GetRenderObject();
				if (currentQuad != currentRenderObj->GetQuad())
				{
					currentQuad = currentRenderObj->GetQuad();
					ID3D11Buffer* vb = currentQuad->GetVertexBuffer();
					context->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
					context->IASetIndexBuffer(currentQuad->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
				}
			}
			int anim = objects[i]->GetRenderObject()->GetCurrentAnimation();
			int frame = objects[i]->GetRenderObject()->GetCurrentFrame();
			currentTex = currentRenderObj->GetTexture(anim, frame);
			context->PSSetShaderResources(0, 1, &currentTex);
			objects[i]->UpdateRenderMatrix();
			cb.world = XMMatrixTranspose(objects[i]->GetRenderObject()->GetWorldMatrix());
			context->UpdateSubresource(m_constantBuffer.Get(), 0, nullptr, &cb, 0, 0);
			context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
			context->DrawIndexed(6, 0, 0);
		}
	}
}

void Graphics::Update(float time)
{
	float speed = 200 * time;
	if (GetAsyncKeyState('W'))
	{
		//m_camera->MovePosition(0, speed, 0);
	}
	if (GetAsyncKeyState('S'))
	{
		//m_camera->MovePosition(0, -speed, 0);
	}
	if (GetAsyncKeyState('A'))
	{
		//m_camera->MovePosition(m_camera->GetLeft() * speed);
	}
	if (GetAsyncKeyState('D'))
	{
		//m_camera->MovePosition(m_camera->GetRight() * speed);
	}
	for (int i = 0; i < m_objectsToRender.size(); i++)
	{
		m_objectsToRender[i]->AnimationUpdate(time);
	}
}

void Graphics::ChangeCameraProjection(float width, float height, float nearZ, float farZ)
{
	m_camera->SetProjectionValues(width, height, nearZ, farZ);
}

RenderedObject* Graphics::GetSpecificRenderObject(int id)
{
	try {
		m_objectsToRender.at(id);
	}
	catch (const std::out_of_range & e)
	{
		return nullptr;
	}
	return m_objectsToRender[id];
}

std::string Graphics::CreateRenderObject(int quadID, int textureID)
{
	try {
		m_quadTypes.at(quadID);
	}
	catch (const std::out_of_range & e)
	{
		return "Quad outside vector range";
	}
	try {

		m_animations.at(textureID).at(0);
	}
	catch (const std::out_of_range & e)
	{
		return "Texture outside vector range";
	}
	RenderedObject* obj = new RenderedObject(*m_quadTypes[quadID], m_animations[textureID]);
	m_objectsToRender.push_back(obj);
	return "Success saved to slot: " + std::to_string(m_objectsToRender.size() - 1);
}

std::string Graphics::CreateAnimatedRenderObject(int quadID, int animationID , float frameTime)
{
	try {
		m_quadTypes.at(quadID);
	}
	catch (const std::out_of_range & e)
	{
		return "Quad outside vector range";
	}
	try {
		m_animations.at(animationID).at(0);
	}
	catch (const std::out_of_range & e)
	{
		return "Animation outside vector range";
	}
	RenderedObject* obj = new RenderedObject(*m_quadTypes[quadID], m_animations[animationID], frameTime);
	m_objectsToRender.push_back(obj);
	return "Success saved to slot: " + std::to_string(m_objectsToRender.size() - 1);
}

/*Texture* Graphics::GetSpecificTexture(int texID)
{
	try {
		m_textures.at(texID);
	}
	catch (const std::out_of_range & e)
	{
		return nullptr;
	}
	return m_textures[texID];
}*/

Texture* Graphics::GetSpecificAnimation(int animID, int frame)
{
	try {
		m_animations.at(animID).at(frame);
	}
	catch (const std::out_of_range & e)
	{
		return nullptr;
	}
	return m_animations[animID][frame];
}

int Graphics::GetNumberOfFrames(int animID)
{
	try {
		m_animations.at(animID).at(0);
	}
	catch (const std::out_of_range & e)
	{
		return 0;
	}
	return m_animations[animID].size();
}

std::string Graphics::CreateTexture(ID3D11Device* device, std::wstring texturePath)
{
	std::vector<Texture*> textures;
	Texture* tex = new Texture();
	bool result;
	result = tex->IntialiseTexture(device, texturePath);
	if (result)
	{
		textures.push_back(tex);
	}
	else
	{
		textures.clear();
		return "Failed to load";
	}
	m_animations.push_back(textures);
	return "Success saved to slot: " + std::to_string(m_animations.size() - 1);
}

std::string Graphics::CreateTextureGroup(ID3D11Device* device, std::vector<std::wstring> texturePath)
{
	std::vector<Texture*> textures;
	for (int i = 0; i < texturePath.size(); i++)
	{
		Texture* tex = new Texture();
		bool result;
		result = tex->IntialiseTexture(device, texturePath[i]);
		if (result)
		{
			textures.push_back(tex);
		}
		else
		{
			for (int i = 0; i < textures.size(); i++)
			{
				delete(textures[i]);
			}
			textures.clear();
			return "Failed to load";
		}
	}
	m_animations.push_back(textures);
	return "Success saved to slot: " + std::to_string(m_animations.size() - 1);
}

std::string Graphics::DeleteTexture(int texID)
{
	try {
		m_animations.at(texID).at(0);
	}
	catch (const std::out_of_range& e)
	{
		return "Outside vector range unable to delete";
	}
	for (int i = 0; i < m_animations[texID].size(); i++)
	{
		delete(m_animations[texID][i]);
	}
	m_animations.erase(m_animations.begin() + texID);
	return "Successfully deleted texture";
}

std::string Graphics::AddAnimationToRenderObject(int objectID, int animationID, float frameTime)
{
	try {
		m_objectsToRender.at(objectID);
	}
	catch (const std::out_of_range & e)
	{
		return "objectID outside vector range";
	}
	try {
		m_animations.at(animationID).at(0);
	}
	catch (const std::out_of_range & e)
	{
		return "Animation outside vector range";
	}
	m_objectsToRender[objectID]->PushAnimationBack(m_animations[animationID],frameTime);
	return "Success animation added to slot: " + std::to_string(m_objectsToRender[objectID]->GetAnimations().size() - 1);
}

void Graphics::AddAnimationToRenderObject(RenderedObject* object, int animationID, float frameTime)
{
	for (int i = 0; i < m_objectsToRender.size(); i++)
	{
		if (m_objectsToRender[i] == object)
		{
			m_objectsToRender[i]->PushAnimationBack(m_animations[animationID], frameTime);
		}
	}
}

std::string Graphics::RemoveAnimationFromRenderObject(int objectID, int animationID)
{
	try {
		m_objectsToRender.at(objectID);
	}
	catch (const std::out_of_range & e)
	{
		return "objectID outside vector range";
	}
	try {
		m_objectsToRender[objectID]->GetAnimations().at(animationID).at(0);
	}
	catch (const std::out_of_range & e)
	{
		return "Animation outside vector range";
	}
	m_objectsToRender[objectID]->RemoveAnimation(animationID);
	return "Animation successfully removed";
}

std::string Graphics::DeleteRenderedObject(int objID)
{
	try {
		m_objectsToRender.at(objID);
	}
	catch (const std::out_of_range & e)
	{
		return "Outside vector range unable to delete";
	}
	m_objectsToRender.erase(m_objectsToRender.begin() + objID);
	return "Successfully deleted Rendered Object";
}
