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
	Texture* test = new Texture(device,L"TestTexture.png");
	m_textures.push_back(test);
	m_camera = new Camera();
	//m_camera->SetProjectionValues(800, 600, 0.1, 50);
	m_camera->SetPosition(0.0f, 0.0f, -2.0f);
	m_camera->SetProjectionValues(90, 800/600, 0.1f, 100.f, true);

	CD3D11_RASTERIZER_DESC rastDesc(D3D11_DEFAULT);
	rastDesc.CullMode = D3D11_CULL_NONE;
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

	CreateRenderObject(0, 0, DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT2(1, 1),DirectX::XMFLOAT3(0,0,0));
	CreateRenderObject(0, 0, DirectX::XMFLOAT3(10, 10, 0), DirectX::XMFLOAT2(10, 10));
	CreateRenderObject(0, 0, DirectX::XMFLOAT3(15, 15, 0), DirectX::XMFLOAT2(10, 10));
	CreateRenderObject(0, 0, DirectX::XMFLOAT3(5, 5, 0), DirectX::XMFLOAT2(10, 10));
	CreateRenderObject(0, 0, DirectX::XMFLOAT3(5, 5, 0), DirectX::XMFLOAT2(10, 10));
	//D3D11_RENDER_TARGET_BLEND_DESC rtbDesc = { 0 };
	//rtbDesc.BlendEnable = true;
}
//Call from inside gameloop
void Graphics::Draw(ID3D11DeviceContext* context)
{
	//compare Quads 
	//set vertex and index buffers
	//set states
	//call each rendered Object

	UINT stride = sizeof(TexturedVertex);
	UINT offset = 0;
	Quad* current = nullptr;
	context->IASetInputLayout(m_vertexShaders[0]->GetInputLayout());
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->RSSetState(m_rasterizerState.Get());
	context->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
	context->VSSetShader(m_vertexShaders[0]->GetShader(), NULL, 0);
	context->PSSetShader(m_pixelShaders[0]->GetShader(), NULL, 0);
	for (int i = 0; i < m_objectsToRender.size(); i++)
	{
		if (current != m_objectsToRender[i]->GetQuad())
		{
			current = m_objectsToRender[i]->GetQuad();
			ID3D11Buffer* vb = current->GetVertexBuffer();
			context->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
			context->IASetIndexBuffer(current->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
		}
		//m_objectsToRender[i]->Draw(context,m_camera->GetOrthoMatrix(),m_camera->GetWorldMatrix() ,m_constantBuffer);
		//context->DrawIndexed(6, 0, 0);	
		ConstantBuffer2D cb;
		//DirectX::XMMATRIX wvpMatrix = m_objectsToRender[i]->GetWorldMatrix() * m_camera->GetOrthoMatrix() * m_camera->GetViewMatrix();
		cb.world = XMMatrixTranspose(m_objectsToRender[i]->GetWorldMatrix());
		//cb.world = XMMatrixTranspose(XMMatrixIdentity());
		cb.view = XMMatrixTranspose(m_camera->GetViewMatrix());
		cb.proj = XMMatrixTranspose(m_camera->GetOrthoMatrix());
		context->UpdateSubresource(m_constantBuffer.Get(), 0, nullptr, &cb, 0, 0);
		context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
		context->PSSetShaderResources(0, 1, m_objectsToRender[i]->GetTexture().GetAddressOf());
		context->DrawIndexed(6, 0, 0);
	}

}

void Graphics::Update(float time)
{
	float speed = 0.1;
	if (GetAsyncKeyState('W'))
	{
		m_camera->MovePosition(m_camera->GetForward() * speed);
	}
	if (GetAsyncKeyState('S'))
	{
		m_camera->MovePosition(m_camera->GetBackward() * speed);
	}
	if (GetAsyncKeyState('A'))
	{
		m_camera->MovePosition(m_camera->GetLeft() * speed);
	}
	if (GetAsyncKeyState('D'))
	{
		m_camera->MovePosition(m_camera->GetRight() * speed);
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		m_camera->MovePosition(0, speed, 0);
	}
}

void Graphics::CreateRenderObject(int quadID, int textureID)
{
	RenderedObject* obj = new RenderedObject(*m_quadTypes[quadID], *m_textures[textureID]);
	m_objectsToRender.push_back(obj);
}

void Graphics::CreateRenderObject(int quadID, int textureID, DirectX::XMFLOAT3 position)
{
	RenderedObject* obj = new RenderedObject(*m_quadTypes[quadID], *m_textures[textureID],position.x,position.y,position.z);
	m_objectsToRender.push_back(obj);
}

void Graphics::CreateRenderObject(int quadID, int textureID, DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 scale)
{
	RenderedObject* obj = new RenderedObject(*m_quadTypes[quadID], *m_textures[textureID], position.x, position.y, position.z,scale.x,scale.y);
	m_objectsToRender.push_back(obj);
}

void Graphics::CreateRenderObject(int quadID, int textureID, DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 scale, DirectX::XMFLOAT3 rotation)
{
	RenderedObject* obj = new RenderedObject(*m_quadTypes[quadID], *m_textures[textureID], position.x, position.y, position.z, scale.x, scale.y,rotation.x,rotation.y,rotation.z);
	m_objectsToRender.push_back(obj);
}
