#include "pch.h"
#include "RenderedObject.h"

RenderedObject::RenderedObject(Quad& quad, std::vector<Texture*> animation)
{
	m_renderQuad = &quad;
	std::vector<ID3D11ShaderResourceView*> base;
	for (int i = 0; i < animation.size(); i++)
	{
		base.push_back(animation[i]->GetTexture());
	}
	m_textures.push_back(base);
	m_frameTimes.push_back(0);
}
RenderedObject::RenderedObject(Quad& quad, std::vector<Texture*> animation,float frameTime)
{
	m_frameTimes.push_back(frameTime);
	m_renderQuad = &quad;
	std::vector<ID3D11ShaderResourceView*> base;
	for (int i = 0; i < animation.size(); i++)
	{
		base.push_back(animation[i]->GetTexture());
	}
	m_textures.push_back(base);
}
ID3D11ShaderResourceView* RenderedObject::GetTexture(int id, int frameID)
{
	return m_textures[id][frameID];
}
void RenderedObject::AnimationUpdate(float time)
{
	m_animTimer += time;
	if (m_animTimer >= m_frameTimes[m_currentAnimation])
	{
		m_animTimer = 0;
		m_frame++;
	}
	if (m_frame >= m_textures[m_currentAnimation].size())
	{
		m_frame = 0;
	}
}
void RenderedObject::UpdateMatrix(DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 scale, DirectX::XMFLOAT3 rotation)
{
	m_worldMatrix = DirectX::XMMatrixScaling(scale.x, scale.y, 1.0f) 
		* DirectX::XMMatrixRotationRollPitchYaw(rotation.x,rotation.y,rotation.z) 
		* DirectX::XMMatrixTranslation(position.x + scale.x / 2, position.y + scale.y / 2, position.z);
}

void RenderedObject::PushAnimationBack(std::vector<Texture*> animation, float frameTime)
{
	m_frameTimes.push_back(frameTime);
	std::vector<ID3D11ShaderResourceView*> base;
	for (int i = 0; i < animation.size(); i++)
	{
		base.push_back(animation[i]->GetTexture());
	}
	m_textures.push_back(base);
}

void RenderedObject::RemoveAnimation(int animID)
{
	m_textures.erase(m_textures.begin() + animID);
	m_frameTimes.erase(m_frameTimes.begin() + animID);
}

std::string RenderedObject::SetCurrentAnimation(int id)
{
	try {
		m_textures.at(id);
	}
	catch (const std::out_of_range & e)
	{
		return "Outside internal animation vector";
	}
	m_currentAnimation = id;
	m_frame = 0;
	m_animTimer = 0;
	return "Successful change animation";
}
