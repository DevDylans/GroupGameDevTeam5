#pragma once
#include "ImGui\imgui.h"
#include "ImGui\imgui_impl_win32.h"
#include "ImGui\imgui_impl_dx11.h"
#include "Graphics.h"

class UserInterface
{
public:
	UserInterface(HWND window, ID3D11Device* device, ID3D11DeviceContext* context,  Graphics& graphics);
	void Draw(ID3D11Device* device);
private:
	Graphics& m_graphics;

	static char sm_textureName[255];
	static std::string sm_resultTextureLoad;
	static std::string sm_resultTextureDelete;
	static int sm_textureDelete;
	static int sm_textureDisplay;
	static ID3D11ShaderResourceView* sm_viewTexture;
	static bool sm_toggleDisplayTexture;

	void RenderTextureInterface(ID3D11Device* device);
};

