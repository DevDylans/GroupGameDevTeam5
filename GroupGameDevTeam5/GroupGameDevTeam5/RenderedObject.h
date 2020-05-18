#pragma once
#include "Quad.h"
#include <DirectXMath.h>
#include "Texture.h"
#include "Structs.h"
class RenderedObject
{
public:
	RenderedObject(Quad& quad, Texture& texture);
	RenderedObject(Quad& quad, Texture& texture, float posX, float posY, float posZ);
	RenderedObject(Quad& quad, Texture& texture, float posX, float posY, float posZ, float scaleX, float scaleY);
	RenderedObject(Quad& quad, Texture& texture, float posX, float posY, float posZ, float scaleX, float scaleY, float rotX, float rotY, float rotZ);

	void Draw(ID3D11DeviceContext* context, DirectX::XMMATRIX orthoMatrix, DirectX::XMMATRIX cameraMatrix, Microsoft::WRL::ComPtr<ID3D11Buffer>& constantBuffer);

	DirectX::XMMATRIX GetWorldMatrix() { return m_worldMatrix; }
	Quad* GetQuad() const { return m_renderQuad; }
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTexture() const { return m_texture; }

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
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	Quad* m_renderQuad;

	DirectX::XMFLOAT3 m_scale;
	DirectX::XMFLOAT3 m_rotation;
	DirectX::XMFLOAT3 m_position;

	DirectX::XMVECTOR m_positionVector;
	DirectX::XMVECTOR m_rotationVector;



};

