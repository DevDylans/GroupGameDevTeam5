#include "pch.h"
#include "LevelFile.h"

LevelFile::LevelFile()
{

}

bool LevelFile::ReadLevelFile()
{
	ifstream levelFile("test level file.txt");
	string line;
	string tempString;

	if (levelFile.is_open())
	{
		while (getline(levelFile, line))
		{
			stringstream ss(line);
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
			getline(ss, tempString, ',');
			m_QuadID = stoi(tempString);
			getline(ss, tempString, ',');
			m_TextureID = stoi(tempString);
			getline(ss, tempString, ',');
			m_FrameTime = stoi(tempString);

			CreateGameObject();
		}
		levelFile.close();
		return true;
	}
	else
	{
		return false;
	}
}

bool LevelFile::WriteLevelFile(vector<GameObject*> gameObjects)
{
	ofstream levelFile("");

	if (levelFile.is_open())
	{
		levelFile << gameObjects. << endl;
		levelFile.close();
		return true;
	}
	else
	{
		return false;
	}
}

void LevelFile::CreateGameObject()
{
	GameObject* gameObject = new GameObject(m_PosX, m_PosY, m_PosZ, m_ScaleX, m_ScaleY, m_RotX, m_RotY, m_RotZ);
	RenderedObject* renderedObject = new RenderedObject(m_QuadID, m_TextureID);
	m_GameObjects.push_back(gameObject);
}

bool LevelFile::ReadRenderedObjectFile()
{
	fstream renderedObjectFile("Rendered Object.txt");
	string line;
	string tempString;

	if (renderedObjectFile.is_open())
	{
		while (getline(renderedObjectFile, line))
		{
			stringstream ss(line);
			getline(ss, tempString, ',');
			m_QuadID = stoi(tempString);
			getline(ss, tempString, ',');
			m_TextureID = stoi(tempString);
			getline(ss, tempString, ',');
			m_FrameTime = stoi(tempString);

			m_Graphics.CreateRenderObject(m_QuadID, m_TextureID);
		}
		renderedObjectFile.close();
		return true;
	}
	else
	{
		return false;
	}
}