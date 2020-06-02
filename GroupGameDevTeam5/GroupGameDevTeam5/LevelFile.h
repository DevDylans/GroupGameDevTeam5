#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "GameObject.h"
#include "Graphics.h"

using namespace std;

class LevelFile
{
public:
	LevelFile();

	bool ReadLevelFile();
	bool WriteLevelFile(vector<GameObject*> gameObjects);

	bool ReadRenderedObjectFile();
	bool WriteRenderedObjectFile();

	vector<GameObject*>& GetGameObjects() {return m_GameObjects;}


private:
	float m_PosX, m_PosY, m_PosZ, m_ScaleX, m_ScaleY, m_RotX, m_RotY, m_RotZ, m_FrameTime;
	int m_QuadID, m_TextureID;
	vector<GameObject*> m_GameObjects;
	Graphics m_Graphics;

	void CreateGameObject();
};