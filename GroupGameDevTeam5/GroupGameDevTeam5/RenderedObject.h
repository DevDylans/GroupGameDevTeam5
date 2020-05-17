#pragma once
#include "Quad.h"
#include <DirectXMath.h>
//#include "TexturedQuad.h"
class RenderedObject
{
public:
	RenderedObject(Microsoft::WRL::ComPtr<ID3D11Device>& device);
	RenderedObject(Microsoft::WRL::ComPtr<ID3D11Device>& device, float scaleX, float scaleY, Quad& quad);

	void Draw(DirectX::XMMATRIX orthoMatrix);

	float GetWidth() const { return m_scale.x; }
	float GetHieght() const { return m_scale.y; }

	void SetScale(float x, float y) { m_scale.x = x; m_scale.y = y; UpdateMatrix();}
	void SetPosition(float x, float y, float z);
	void MovePosition(float x, float y, float z);
	void MovePosition(const DirectX::XMVECTOR& pos);
	void SetRotation(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void Rotate(DirectX::XMVECTOR& pos);
private:
	void UpdateMatrix();

	DirectX::XMMATRIX m_worldMatrix = DirectX::XMMatrixIdentity();
	ID3D11Texture2D* m_texture;
	ID3D11DeviceContext* m_deviceContext = nullptr;

	Quad* m_renderQuad;

	DirectX::XMFLOAT3 m_scale;
	DirectX::XMFLOAT3 m_rotation;
	DirectX::XMFLOAT3 m_position;

	DirectX::XMVECTOR m_positionVector;
	DirectX::XMVECTOR m_rotationVector;



};

