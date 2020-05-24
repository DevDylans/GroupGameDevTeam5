#include "pch.h"
#include "UserInterface.h"

std::string UserInterface::sm_resultTextureLoad = "";
std::string UserInterface::sm_resultTextureDelete = "";
char UserInterface::sm_textureName[255] = "";
int UserInterface::sm_textureDelete = 0;
int UserInterface::sm_textureDisplay= 0;
ID3D11ShaderResourceView* UserInterface::sm_viewTexture = nullptr;
bool UserInterface::sm_toggleDisplayTexture = false;

UserInterface::UserInterface(HWND window, ID3D11Device* device, ID3D11DeviceContext* context,  Graphics& graphics) : m_graphics(graphics)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(device, context);
    ImGui::StyleColorsDark();
}

void UserInterface::Draw(ID3D11Device* device)
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    RenderTextureInterface(device);

    ImGui::Render();

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UserInterface::RenderTextureInterface(ID3D11Device* device)
{
    ImGui::Begin("Load A Texture");
    ImGui::InputText("Path to texture", sm_textureName, 255);
    if (ImGui::Button("Load Texture"))
    {
        std::string texName = sm_textureName; //= std::string(textureName);
        std::wstring convertedTexName(texName.length(), L' ');
        std::copy(texName.begin(), texName.end(), convertedTexName.begin());
        sm_resultTextureLoad = m_graphics.CreateTexture(device, convertedTexName); //setup Return value/stops creation if not valid and returns messeage, 
    }
    ImGui::Text(sm_resultTextureLoad.c_str());
    ImGui::InputInt("Texture to delete", &sm_textureDelete);
    if (ImGui::Button("Delete Texture"))
    {
        sm_resultTextureDelete = m_graphics.DeleteTexture(sm_textureDelete);
    }
    ImGui::Text(sm_resultTextureDelete.c_str());
    ImGui::InputInt("Texture to display", &sm_textureDisplay);
    ImGui::Checkbox("Display desired Texture?",&sm_toggleDisplayTexture);
    if (ImGui::Button("Display Texture"))
    {
        sm_viewTexture = m_graphics.GetSpecificTexture(sm_textureDisplay)->GetTexture();
    }
    if (sm_toggleDisplayTexture)
    {
        ImGui::Begin("Display Texture");
        ImGui::Image((void*)sm_viewTexture, ImVec2(256, 256));
        ImGui::End();
    }

    ImGui::End();
}
