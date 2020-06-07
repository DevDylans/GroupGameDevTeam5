#include "pch.h"
#include "LevelFile.h"

LevelFile::LevelFile()
{

}

bool LevelFile::ReadLevelFile()
{
	ifstream levelFile("Level.txt");
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
			m_RenderedObjectID = stoi(tempString);

			CreateGameObject();
			m_RenderIDs.push_back(m_RenderedObjectID);
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
		//levelFile << gameObjects. << endl;
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
	m_GameObjects.push_back(gameObject);
}

bool LevelFile::ReadRenderedObjectFile()
{
	fstream renderedObjectFile("Rendered Objects.txt");
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

			CreateRenderedObject();
		}
		renderedObjectFile.close();
		return true;
	}
	else
	{
		return false;
	}
}

void LevelFile::CreateRenderedObject()
{
	m_RenderedObjects.push_back(m_QuadID);
	m_RenderedObjects.push_back(m_TextureID);
	m_RenderedObjects.push_back(m_FrameTime);
}

bool LevelFile::ReadTextureFile()
{
	fstream TextureFile("Textures.txt");
	string line;
	wstring tempWstring;

	if (TextureFile.is_open())
	{
		while (getline(TextureFile, line))
		{
			//m_TexturePath = line;

			CreateTexture();
		}
		TextureFile.close();
		return true;
	}
	else
	{
		return false;
	}
}

void LevelFile::CreateTexture()
{
	m_Textures.push_back(m_TexturePath);
}