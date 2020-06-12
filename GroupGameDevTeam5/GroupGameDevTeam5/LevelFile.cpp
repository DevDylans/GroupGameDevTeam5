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
			m_PosX = stof(tempString);
			getline(ss, tempString, ',');
			m_PosY = stof(tempString);
			getline(ss, tempString, ',');
			m_PosZ = stof(tempString);
			getline(ss, tempString, ',');
			m_ScaleX = stof(tempString);
			getline(ss, tempString, ',');
			m_ScaleY = stof(tempString);
			getline(ss, tempString, ',');
			m_RotX = stof(tempString);
			getline(ss, tempString, ',');
			m_RotY = stof(tempString);
			getline(ss, tempString, ',');
			m_RotZ = stof(tempString);
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
	ofstream levelFile("Level save test.txt");
	if (levelFile.is_open())
	{
		for (int i = 0; i < m_GameObjects.size(); i++)
		{
			levelFile << m_GameObjects[i]->GetTransform().GetPosition().x << ','
				<< m_GameObjects[i]->GetTransform().GetPosition().y << ','
				<< m_GameObjects[i]->GetTransform().GetPosition().z << ','
				<< m_GameObjects[i]->GetTransform().GetScale().x << ','
				<< m_GameObjects[i]->GetTransform().GetScale().y << ','
				<< m_GameObjects[i]->GetTransform().GetRotation().x << ','
				<< m_GameObjects[i]->GetTransform().GetRotation().y << ','
				<< m_GameObjects[i]->GetTransform().GetRotation().z << ','
				<< m_outputRenderIDs[i]
				<< endl;
		}
		m_outputRenderIDs.clear();
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

bool LevelFile::WriteRenderedObjectFile(Graphics graphics)
{
	ofstream renderedObjectFile("RO save test.txt");

	if (renderedObjectFile.is_open())
	{
		for (int i = 0; i < graphics.GetObjectsToRender().size(); i++) //quad, anim, frametime
		{
			renderedObjectFile << 0 << ',';
			for (int j = 0; j < graphics.GetAnimations().size(); j++)
			{
				if (graphics.GetSpecificAnimation(j, 0)->GetTexture() == graphics.GetSpecificRenderObject(i)->GetAnimations()[0][0])
				{
					renderedObjectFile << j << ',';
					j = 10000;
				}
			}
			renderedObjectFile << graphics.GetSpecificRenderObject(i)->GetAnimationTimes()[0] << endl;
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

bool LevelFile::WriteTextureFile(Graphics graphics)
{
	ofstream TextureFile("Texture save test.txt");
	string tempString;

	using convert_t = std::codecvt_utf8<wchar_t>;
	wstring_convert<convert_t, wchar_t> strconverter;

	if (TextureFile.is_open())
	{
		for (int i = 0; i < graphics.GetAnimations().size(); i++)
		{
			TextureFile << strconverter.to_bytes(graphics.GetSpecificAnimation(i,0)->textureName) << endl;
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
