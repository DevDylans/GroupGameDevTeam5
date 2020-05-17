#pragma once
class Camera
{
public:
	Camera();
	void SetProjectionValues(float width, float height, float nearZ, float farZ);
	const DirectX::XMMATRIX& GetOrthoMatrix() const { return m_orthoMatrix; }
	const DirectX::XMMATRIX& GetWorldMatrix() const { return m_worldMatrix; }

	void SetPosition(float x, float y, float z);
	void MovePosition(float x, float y, float z);
	void MovePosition(const DirectX::XMVECTOR& pos);
	void SetRotation(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void Rotate(DirectX::XMVECTOR& pos);
private:
	void UpdateMatrix();
	DirectX::XMMATRIX m_orthoMatrix;
	DirectX::XMMATRIX m_worldMatrix;
	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_rotation;
	DirectX::XMVECTOR m_positionVector;
	DirectX::XMVECTOR m_rotationVector;
};

