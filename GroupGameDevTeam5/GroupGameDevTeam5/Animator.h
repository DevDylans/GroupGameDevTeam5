#pragma once
#include "RenderedObject.h"
class Animator :
	public RenderedObject
{
public:
	Animator(Quad& quad, std::vector<Texture*> animation, float frameTime);

private:
	int m_frame;
	float m_animTimer;
	float m_frameTime;
};

