#pragma once
#include "Quad.h"
#include <DirectXMath.h>
#include "Texture.h"
#include <vector>
class RenderedObject
{
public:
	RenderedObject(Quad& quad, Texture& texture);
	RenderedObject(Quad& quad, std::vector<Texture*> animation, float frameTime);

	DirectX::XMMATRIX GetWorldMatrix() { return m_worldMatrix; }
	Quad* GetQuad() const { return m_renderQuad; }
	ID3D11ShaderResourceView* GetTexture(int id, int frameID);
	int GetCurrentAnimation() { return m_currentAnimation; }
	int GetCurrentFrame() { return m_frame; }

	void AnimationUpdate(float time);
	void UpdateMatrix(DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 scale, DirectX::XMFLOAT3 rotation);
	void PushAnimationBack(std::vector<Texture*> animation,float frameTime);
	void RemoveAnimation(int animID);
	std::string SetCurrentAnimation(int id);
	std::vector<std::vector<ID3D11ShaderResourceView*>> GetAnimations() { return m_textures; }
private:
	DirectX::XMMATRIX m_worldMatrix = DirectX::XMMatrixIdentity();
	std::vector<std::vector<ID3D11ShaderResourceView*>> m_textures;
	std::vector<float> m_frameTimes;
	Quad* m_renderQuad;

	int m_currentAnimation = 0;
	int m_frame = 0;
	float m_animTimer = 0;
};

