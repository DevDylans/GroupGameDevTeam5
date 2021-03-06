#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <codecvt>
#include <locale>
#include "GameObject.h"
#include "Graphics.h"

using namespace std;

class LevelFile
{
public:
	LevelFile();

	bool ReadLevelFile();
	bool WriteLevelFile(int renderedObjectID);

	bool ReadRenderedObjectFile();
	bool WriteRenderedObjectFile(Graphics graphics);

	bool ReadTextureFile();
	bool WriteTextureFile(Graphics graphics);
	
	void AddRenderID(int id) { m_outputRenderIDs.push_back(id); }

	vector<GameObject*>& GetGameObjects() {return m_GameObjects;}
	vector<int> GetRenderIDs() { return m_RenderIDs; }
	vector<int> GetRenderedObjects() { return m_RenderedObjects; }
	vector<wstring> GetTextures() { return m_Textures; }

private:
	float m_PosX, m_PosY, m_PosZ, m_ScaleX, m_ScaleY, m_RotX, m_RotY, m_RotZ, m_FrameTime = 0.0;
	int m_QuadID, m_TextureID, m_RenderedObjectID = 0;
	wstring m_TexturePath;

	vector<GameObject*> m_GameObjects;
	vector<int> m_RenderIDs;
	vector<int> m_RenderedObjects;
	vector<wstring> m_Textures;
	vector<int> m_outputRenderIDs;

	void CreateGameObject();
	void CreateRenderedObject();
	void CreateTexture();
};