#include "pch.h"
#include "Animator.h"

Animator::Animator(Quad& quad, std::vector<Texture*> animation, float frameTime) : RenderedObject(quad,animation)
{
	m_frame = 0;
	m_animTimer = 0;
	m_frameTime = frameTime;
}
