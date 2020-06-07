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

	bool ReadLevelFile();
	bool WriteLevelFile(vector<GameObject*> gameObjects);

	bool ReadRenderedObjectFile();
	bool WriteRenderedObjectFile();

	bool ReadTextureFile();
	bool WriteTextureFile();

	vector<GameObject*>& GetGameObjects() {return m_GameObjects;}
	vector<int> GetRenderIDs() { return m_RenderIDs; }
	vector<int> GetRenderedObjects() { return m_RenderedObjects; }
	vector<wstring> GetTextures() { return m_Textures; }

private:
	float m_PosX, m_PosY, m_PosZ, m_ScaleX, m_ScaleY, m_RotX, m_RotY, m_RotZ, m_FrameTime;
	int m_QuadID, m_TextureID, m_RenderedObjectID;
	wstring m_TexturePath;

	vector<GameObject*> m_GameObjects;
	vector<int> m_RenderIDs;
	vector<int> m_RenderedObjects;
	vector<wstring> m_Textures;

	void CreateGameObject();
	void CreateRenderedObject();
	void CreateTexture();
};