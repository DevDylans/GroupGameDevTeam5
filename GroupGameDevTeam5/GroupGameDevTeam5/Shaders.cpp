#include "pch.h"
#include "Shaders.h"

void VertexShader::CreateShader(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderPath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements)
{
	ID3DBlob* VSBlob = nullptr;
	DX::ThrowIfFailed(D3DReadFileToBlob(shaderPath.c_str(),&VSBlob));
	DX::ThrowIfFailed(device->CreateVertexShader(VSBlob->GetBufferPointer(), VSBlob->GetBufferSize(), NULL, m_shader.GetAddressOf()));
	DX::ThrowIfFailed(device->CreateInputLayout(layoutDesc, numElements, VSBlob->GetBufferPointer(), VSBlob->GetBufferSize(), m_inputLayout.GetAddressOf()));
	VSBlob->Release();
}

void PixelShader::CreateShader(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderPath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements)
{
	ID3DBlob* PSBlob = nullptr;
	DX::ThrowIfFailed(D3DReadFileToBlob(shaderPath.c_str(), &PSBlob));
	DX::ThrowIfFailed(device->CreatePixelShader(PSBlob->GetBufferPointer(), PSBlob->GetBufferSize(), NULL, m_shader.GetAddressOf()));
	PSBlob->Release();
}
