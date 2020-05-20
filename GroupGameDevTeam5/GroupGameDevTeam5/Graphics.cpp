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
	m_camera->SetProjectionValues(800, 600, 0.1, 50);


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

}

//call from inside gameloop
void Graphics::DrawNoAnim(ID3D11DeviceContext* context, int shaderID, std::vector<GameObject*> objects)
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
			if (currentTex != currentRenderObj->GetTexture(0,0))
			{
				currentTex = currentRenderObj->GetTexture(0,0);
				context->PSSetShaderResources(0, 1, &currentTex);
			}
		}
		objects[i]->UpdateRenderMatrix();
		cb.world = XMMatrixTranspose(objects[i]->GetRenderObject()->GetWorldMatrix());
		context->UpdateSubresource(m_constantBuffer.Get(), 0, nullptr, &cb, 0, 0);
		context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
		context->DrawIndexed(6, 0, 0);
	}
}

void Graphics::DrawNoAnim(ID3D11DeviceContext* context, int shaderID, GameObject* object)
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
	ID3D11ShaderResourceView* currentTex = object->GetRenderObject()->GetTexture(0,0);
	context->PSSetShaderResources(0, 1, &currentTex);
	object->UpdateRenderMatrix();
	cb.world = XMMatrixTranspose(object->GetRenderObject()->GetWorldMatrix());
	context->UpdateSubresource(m_constantBuffer.Get(), 0, nullptr, &cb, 0, 0);
	context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
	context->DrawIndexed(6, 0, 0);
}

void Graphics::Update(float time)
{
	float speed = 100 * time;
	if (GetAsyncKeyState('W'))
	{
		m_camera->MovePosition(0, speed, 0);
	}
	if (GetAsyncKeyState('S'))
	{
		m_camera->MovePosition(0, -speed, 0);
	}
	if (GetAsyncKeyState('A'))
	{
		m_camera->MovePosition(m_camera->GetLeft() * speed);
	}
	if (GetAsyncKeyState('D'))
	{
		m_camera->MovePosition(m_camera->GetRight() * speed);
	}
}

void Graphics::CreateRenderObject(int quadID, int textureID)
{
	RenderedObject* obj = new RenderedObject(*m_quadTypes[quadID], *m_textures[textureID]);
	m_objectsToRender.push_back(obj);
}

void Graphics::CreateTexture(ID3D11Device* device, std::wstring texturePath)
{
	Texture* tex = new Texture(device,texturePath);
	m_textures.push_back(tex);
}
