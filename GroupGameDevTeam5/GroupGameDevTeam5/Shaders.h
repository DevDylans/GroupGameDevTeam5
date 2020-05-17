#pragma once
#include <d3dcompiler.h>
#include <wrl\client.h>
#include <string>

class VertexShader
{
public:
	void CreateShader(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderPath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements);
	ID3D11VertexShader* GetShader() const {	return m_shader.Get(); }
	ID3D11InputLayout* GetInputLayout() const { return m_inputLayout.Get(); }

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
};
class PixelShader
{
public:
	void CreateShader(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderPath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements);
	ID3D11PixelShader* GetShader() const { return m_shader.Get(); }

private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_shader;
};

