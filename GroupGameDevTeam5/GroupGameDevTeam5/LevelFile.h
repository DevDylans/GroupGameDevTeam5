#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <codecvt>
#include <locale>
#include "GameObject.h"

using namespace std;

class LevelFile
{
public:
	LevelFile();

	bool ReadLevelFile();
	bool WriteLevelFile(int renderedObjectID);

	bool ReadRenderedObjectFile();
	bool WriteRenderedObjectFile();

	bool ReadTextureFile();
	bool WriteTextureFile();

	vector<GameObject*>& GetGameObjects() {return m_GameObjects;}
	vector<int> GetRenderIDs() { return m_RenderIDs; }
	vector<int> GetRenderedObjectsQuadIDs() { return m_QuadIDs; }
	vector<int> GetRenderedObjectsTextureIDs() { return m_TextureIDs; }
	vector<float> GetRenderedObjectsFrameTimes() { return m_FrameTimes; }
	vector<wstring> GetTextures() { return m_Textures; }

private:
	float m_PosX, m_PosY, m_PosZ, m_ScaleX, m_ScaleY, m_RotX, m_RotY, m_RotZ, m_FrameTime = 0.0;
	int m_QuadID, m_TextureID, m_RenderedObjectID = 0;
	wstring m_TexturePath;

	vector<GameObject*> m_GameObjects;
	vector<int> m_RenderIDs;
	vector<int> m_QuadIDs;
	vector<int> m_TextureIDs;
	vector<float> m_FrameTimes;
	vector<wstring> m_Textures;

	void CreateGameObject();
	void CreateRenderedObject();
	void CreateTexture();
};