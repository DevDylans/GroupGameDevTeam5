#include "pch.h"
#include "LevelFile.h"

LevelFile::LevelFile()
{
	string path = "test level file.txt";
	ReadFile(path);
	//WriteFile(path);
}

bool LevelFile::ReadFile(string path)
{
	ifstream levelFile(path);
	string line;
	string tempString;

	if (levelFile.is_open())
	{
		while (getline(levelFile, line))
		{
			stringstream ss(line);
			getline(ss, m_GameObjectID, ',');
			getline(ss, tempString, ',');
			m_PosX = stoi(tempString);
			getline(ss, tempString, ',');
			m_PosY = stoi(tempString);
			getline(ss, tempString, ',');
			m_PosZ = stoi(tempString);
			getline(ss, tempString, ',');
			m_ScaleX = stoi(tempString);
			getline(ss, tempString, ',');
			m_ScaleY = stoi(tempString);
			getline(ss, tempString, ',');
			m_RotX = stoi(tempString);
			getline(ss, tempString, ',');
			m_RotY = stoi(tempString);
			getline(ss, tempString, ',');
			m_RotZ = stoi(tempString);
		}
		levelFile.close();
		return true;
	}
	else
	{
		return false;
	}
}

bool LevelFile::WriteFile(string path)
{
	ofstream levelFile(path);

	if (levelFile.is_open())
	{
		levelFile << "test_write" << endl;
		levelFile.close();
		return true;
	}
	else
	{
		return false;
	}
}
void LevelFile::CreateGameObject(float posX, float posY, float posZ, float scaleX, float scaleY, float rotX, float rotY, float rotZ)
{
	
}