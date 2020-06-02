#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "GameObject.h"

using namespace std;

class LevelFile
{
public:
	LevelFile();

	bool ReadFile(string path);
	bool WriteFile(string path);

	vector<GameObject*>& GetGameObjects() {return m_GameObjects;}

private:
	//GameObject m_GameObject;
	float m_PosX, m_PosY, m_PosZ, m_ScaleX, m_ScaleY, m_RotX, m_RotY, m_RotZ;
	vector<GameObject*> m_GameObjects;

	void CreateGameObject();
};