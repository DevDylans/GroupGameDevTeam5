#pragma once
#include "ImGui\imgui.h"
#include "ImGui\imgui_impl_win32.h"
#include "ImGui\imgui_impl_dx11.h"
#include "Graphics.h"
#include "LevelFile.h"
#include <sstream>

class UserInterface
{
public:
	UserInterface(HWND window, ID3D11Device* device, ID3D11DeviceContext* context,  Graphics& graphics, LevelFile& levelFile);
	void Draw(ID3D11Device* device, std::vector<GameObject*>& gameObjects);
private:
	Graphics& m_graphics;
	LevelFile& m_LevelFile;

	static char sm_textureName[255];
	static char sm_animationPaths[1200];
	static std::string sm_resultTextureLoad;
	static std::string sm_resultTextureDelete;
	static std::string sm_resultAnimationLoad;
	static int sm_textureDelete;
	static int sm_textureDisplay;
	static ID3D11ShaderResourceView* sm_viewTexture;
	static bool sm_toggleDisplayTexture;
	static bool sm_displayTextureExists;
	static std::string sm_animationFrameNames;
	static int sm_animationDisplay;
	static bool sm_toggleAnimationDisplay;
	static bool sm_animationExists;
	static int sm_currentFrame;
	static int sm_counterForFrameDisplay;
	static ID3D11ShaderResourceView* sm_viewAnimation;
	static int sm_displayedAnimationID;
	static int sm_displayedTextureID;

	static int sm_renderedObjectID;
	static int sm_displayedRenderObjectID;
	static int sm_textureToAttach;
	static int sm_quadToAttatch;
	static int sm_aniamtionToAttatch;
	static int sm_aniamtionInternal;
	static float sm_animationTimer;
	static std::string sm_resultRenderObjectCreation;
	static std::string sm_resultRenderObjectAnimationCreation;
	static std::string sm_resultAddAnimation;
	static std::string sm_resultRemoveAnimation;
	static std::string sm_resultUpdateCurrentAnimation;
	static std::string sm_resultDeleteRenderedObject;
	static bool sm_toggleDisplayRenderedObject;
	static RenderedObject* sm_renderedObject;
	static ID3D11ShaderResourceView* sm_viewRenderedObject;
	static bool sm_renderedObjectExists;

	static float sm_positionCreation[3];
	static float sm_scaleCreation[2];
	static float sm_rotationCreation[3];
	static int sm_renderedObjectAttatch;
	static std::string sm_resultGameObjectCreation;
	static int sm_selectedGameObject;
	static float sm_currentPosition[3];
	static float sm_currentScale[2];
	static float sm_currentRotation[3];
	static std::string sm_resultMoveObject;
	static int sm_editingGameObject;
	static bool sm_editingEnabled;
	static char sm_saveFile[255];
	//static std::string sm_loadFile;

	void RenderTextureInterface(ID3D11Device* device);
	void RenderedObjectInterface(ID3D11Device* device);
	void GameObjectInterface(ID3D11Device* device, std::vector<GameObject*>& gameObjects);
};

