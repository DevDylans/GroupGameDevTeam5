#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include "GameObject.h"

using namespace std;

class LevelFile
{
public:
	LevelFile();

	bool ReadFile(string path);
	bool WriteFile(string path);

	void CreateGameObject(float posX, float posY, float posZ, float scaleX, float scaleY, float rotX, float rotY, float rotZ);

private:
	//GameObject m_GameObject;
	string m_GameObjectID;
	float m_PosX, m_PosY, m_PosZ, m_ScaleX, m_ScaleY, m_RotX, m_RotY, m_RotZ;
};