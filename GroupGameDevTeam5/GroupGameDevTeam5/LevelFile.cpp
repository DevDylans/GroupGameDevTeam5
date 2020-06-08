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

bool LevelFile::WriteLevelFile(int renderedObjectID)
{
	ofstream levelFile("Level.txt");

	if (levelFile.is_open())
	{
		for (int i = 0; i > m_GameObjects.size(); i++)
		{
			levelFile << m_GameObjects[i]->GetTransform().GetPosition().x << ','
				<< m_GameObjects[i]->GetTransform().GetPosition().y << ','
				<< m_GameObjects[i]->GetTransform().GetPosition().z << ',' 
				<< m_GameObjects[i]->GetTransform().GetScale().x << ','
				<< m_GameObjects[i]->GetTransform().GetScale().y << ','
				<< m_GameObjects[i]->GetTransform().GetRotation().x << ','
				<< m_GameObjects[i]->GetTransform().GetRotation().y << ','
				<< m_GameObjects[i]->GetTransform().GetRotation().z << ','
				<< renderedObjectID 
				<< endl;
		}
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

bool LevelFile::WriteRenderedObjectFile()
{
	ofstream renderedObjectFile("Rendered Objects.txt");

	if (renderedObjectFile.is_open())
	{
		for (int i = 0; i < m_QuadIDs.size(); i++)
		{
			renderedObjectFile << m_QuadIDs[i] << ','
				<< m_TextureIDs[i] << ','
				<< m_FrameTimes[i] << ','
				<< endl;
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
	m_QuadIDs.push_back(m_QuadID);
	m_TextureIDs.push_back(m_TextureID);
	m_FrameTimes.push_back(m_FrameTime);
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
			wstring convertedLine(line.length(), L' ');
			copy(line.begin(), line.end(), convertedLine.begin());
			m_TexturePath = convertedLine;

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

bool LevelFile::WriteTextureFile()
{
	ofstream TextureFile("Textures.txt");
	string tempString;

	using convert_t = std::codecvt_utf8<wchar_t>;
	wstring_convert<convert_t, wchar_t> strconverter;

	if (TextureFile.is_open())
	{
		for (int i = 0; i < m_Textures.size(); i++)
		{
			TextureFile << strconverter.to_bytes(m_Textures[i]) << endl;
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