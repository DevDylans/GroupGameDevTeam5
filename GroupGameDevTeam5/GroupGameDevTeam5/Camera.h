#pragma once
class Camera
{
public:
	Camera();
	void SetProjectionValues(float width, float height, float nearZ, float farZ);
	const DirectX::XMMATRIX& GetOrthoMatrix() const { return m_orthoMatrix; }
	const DirectX::XMMATRIX& GetViewMatrix() const { return m_viewMatrix; }
	DirectX::XMVECTOR GetForward() { return m_camForwad; }
	DirectX::XMVECTOR GetBackward() { return m_camBack; }
	DirectX::XMVECTOR GetRight() { return m_camRight; }
	DirectX::XMVECTOR GetLeft() { return m_camLeft; }

	void SetPosition(float x, float y, float z);
	void MovePosition(float x, float y, float z);
	void MovePosition(const DirectX::XMVECTOR& pos);
	void SetRotation(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void Rotate(DirectX::XMVECTOR& pos);
private:
	void UpdateMatrix();
	DirectX::XMMATRIX m_orthoMatrix;
	DirectX::XMMATRIX m_viewMatrix;
	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_rotation;
	DirectX::XMVECTOR m_positionVector;
	DirectX::XMVECTOR m_rotationVector;

	DirectX::XMVECTOR m_camUp = DirectX::XMVectorSet(0.f, 1.f, 0.f, 0.f);

	DirectX::XMVECTOR m_defaultForward = DirectX::XMVectorSet(0.f, 0.f, 1.f, 0.f);
	DirectX::XMVECTOR m_defaultRight = DirectX::XMVectorSet(1.f, 0.f, 0.f, 0.f);
	DirectX::XMVECTOR m_defaultBack = DirectX::XMVectorSet(0.f, 0.f, -1.f, 0.f);
	DirectX::XMVECTOR m_defaultLeft = DirectX::XMVectorSet(-1.f, 0.f, 0.f, 0.f);

	DirectX::XMVECTOR m_camForwad = DirectX::XMVectorSet(0.f, 0.f, 1.f, 0.f);
	DirectX::XMVECTOR m_camRight = DirectX::XMVectorSet(1.f, 0.f, 0.f, 0.f);
	DirectX::XMVECTOR m_camLeft = DirectX::XMVectorSet(-1.f, 0.f, 0.f, 0.f);
	DirectX::XMVECTOR m_camBack = DirectX::XMVectorSet(0.f, 0.f, -1.f, 0.f);
};

