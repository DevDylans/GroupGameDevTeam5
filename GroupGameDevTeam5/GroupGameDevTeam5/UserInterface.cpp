#include "pch.h"
#include "UserInterface.h"

std::string UserInterface::sm_resultTextureLoad = "";
std::string UserInterface::sm_resultTextureDelete = "";
std::string UserInterface::sm_resultAnimationLoad = "";
char UserInterface::sm_textureName[255] = "";
char UserInterface::sm_animationPaths[1200] = "";
int UserInterface::sm_textureDelete = 0;
int UserInterface::sm_textureDisplay= 0;
ID3D11ShaderResourceView* UserInterface::sm_viewTexture = nullptr;
std::string UserInterface::sm_animationFrameNames = "";
bool UserInterface::sm_toggleDisplayTexture = false;
bool UserInterface::sm_displayTextureExists = false;
int UserInterface::sm_animationDisplay = 0;
bool UserInterface::sm_toggleAnimationDisplay = false;
bool UserInterface::sm_animationExists = false;
int UserInterface::sm_currentFrame = 0;
int UserInterface::sm_counterForFrameDisplay = 0;
ID3D11ShaderResourceView* UserInterface::sm_viewAnimation = nullptr;
int UserInterface::sm_displayedAnimationID = 0;
int UserInterface::sm_displayedTextureID = 0;

int UserInterface::sm_renderedObjectID = 0;
int UserInterface::sm_displayedRenderObjectID = 0;
int UserInterface::sm_textureToAttach = 0;
int UserInterface::sm_quadToAttatch = 0;
int UserInterface::sm_aniamtionToAttatch = 0;
int UserInterface::sm_aniamtionInternal = 0;
std::string UserInterface::sm_resultRenderObjectCreation = "";
std::string UserInterface::sm_resultRenderObjectAnimationCreation = "";
std::string UserInterface::sm_resultAddAnimation = "";
std::string UserInterface::sm_resultRemoveAnimation = "";
std::string UserInterface::sm_resultUpdateCurrentAnimation = "";
std::string UserInterface::sm_resultDeleteRenderedObject = "";
float UserInterface::sm_animationTimer = 0.f;
bool UserInterface::sm_toggleDisplayRenderedObject = false;
RenderedObject* UserInterface::sm_renderedObject = nullptr;
bool UserInterface::sm_renderedObjectExists = false;
ID3D11ShaderResourceView* UserInterface::sm_viewRenderedObject = nullptr;

float UserInterface::sm_positionCreation[3] = { 0.0f,0.0f,0.0f };
float UserInterface::sm_scaleCreation[2] = { 10.0f,10.0f };
float UserInterface::sm_rotationCreation[3] = { 0.0f,0.0f,0.0f };
std::string UserInterface::sm_resultGameObjectCreation = "";
int UserInterface::sm_renderedObjectAttatch = -1;
int UserInterface::sm_selectedGameObject = 0;
float UserInterface::sm_currentPosition[3] = { 0.0f,0.0f,0.0f };;
float UserInterface::sm_currentScale[2] = { 10.0f,10.0f };
float UserInterface::sm_currentRotation[3] = { 0.0f,0.0f,0.0f };
std::string UserInterface::sm_resultMoveObject = "";
int UserInterface::sm_editingGameObject = 0;
bool UserInterface::sm_editingEnabled = false;
char UserInterface::sm_saveFile[255] = "";

UserInterface::UserInterface(HWND window, ID3D11Device* device, ID3D11DeviceContext* context,  Graphics& graphics) : m_graphics(graphics)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(device, context);
    ImGui::StyleColorsDark();
}

void UserInterface::Draw(ID3D11Device* device, std::vector<GameObject*> &gameObjects)
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    RenderTextureInterface(device);
    RenderedObjectInterface(device);
    GameObjectInterface(device,gameObjects);

    ImGui::Render();

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UserInterface::RenderTextureInterface(ID3D11Device* device)
{
    ImGui::Begin("Load A Texture");
    ImGui::InputText("Path to texture", sm_textureName, 255);
    if (ImGui::Button("Load Texture"))
    {
        std::string texName = sm_textureName;
        std::wstring convertedTexName(texName.length(), L' ');
        std::copy(texName.begin(), texName.end(), convertedTexName.begin());
        sm_resultTextureLoad = m_graphics.CreateTexture(device, convertedTexName); //setup Return value/stops creation if not valid and returns messeage, 
    }
    ImGui::Text(sm_resultTextureLoad.c_str());
    ImGui::InputInt("Texture to delete", &sm_textureDelete);
    if (ImGui::Button("Delete Texture (Warning may crash if in use)"))
    {
        sm_resultTextureDelete = m_graphics.DeleteTexture(sm_textureDelete);
    }
    ImGui::Text(sm_resultTextureDelete.c_str());
    ImGui::InputInt("Texture to display", &sm_textureDisplay);
    ImGui::Checkbox("Display desired Texture?",&sm_toggleDisplayTexture);
    if (ImGui::Button("Display Texture"))
    {
        sm_displayTextureExists = m_graphics.GetSpecificTexture(sm_textureDisplay);
        if (sm_displayTextureExists)
        {
            sm_viewTexture = m_graphics.GetSpecificTexture(sm_textureDisplay)->GetTexture();
            sm_displayedTextureID = sm_textureDisplay;
        }
    }
    if (sm_toggleDisplayTexture)
    {
        ImGui::Begin("Display Texture");
        std::string string = "Displaying Texture: " + std::to_string(sm_displayedTextureID);
        ImGui::Text(string.c_str());
        ImGui::Image((void*)sm_viewTexture, ImVec2(256, 256));
        ImGui::End();
    }
    ImGui::Text("Animations");
    ImGui::Text("Paths To Frames (Seperate paths by lines)");
    ImGui::InputTextMultiline("", sm_animationPaths,1200,ImVec2(420,64));
    if (ImGui::Button("Load Animation"))
    {
        std::stringstream fullStream(sm_animationPaths);
        std::string name;
        std::vector<std::wstring> names;
        while (std::getline(fullStream, name, '\n'))
        {
            std::wstring convertedAnimName(name.length(), L' ');
            std::copy(name.begin(), name.end(), convertedAnimName.begin());
            names.push_back(convertedAnimName);
        }
        sm_resultAnimationLoad = m_graphics.CreateTextureGroup(device, names);
    }
    ImGui::Text(sm_resultAnimationLoad.c_str());
    ImGui::InputInt("Animation to display", &sm_animationDisplay);
    ImGui::Checkbox("Display desired animation?", &sm_toggleAnimationDisplay);
    if (ImGui::Button("Display Animation"))
    {
        sm_animationExists = m_graphics.GetSpecificAnimation(sm_animationDisplay, sm_currentFrame);
        if (sm_animationExists)
        {
            sm_displayedAnimationID = sm_animationDisplay;
        }
    }
    if (sm_toggleAnimationDisplay)
    {
        ImGui::Begin("Display Animation");
        std::string string = "Displaying Animation: " + std::to_string(sm_displayedAnimationID);
        std::string frames = "Number of Frames: " + std::to_string(m_graphics.GetNumberOfFrames(sm_displayedAnimationID));
        ImGui::Text(string.c_str());
        ImGui::Text(frames.c_str());
        sm_viewAnimation = m_graphics.GetSpecificAnimation(sm_displayedAnimationID, sm_currentFrame)->GetTexture();
        sm_counterForFrameDisplay++;
        if (sm_counterForFrameDisplay > 50)
        {
            sm_currentFrame++;
            sm_counterForFrameDisplay = 0;
            if (sm_currentFrame >= m_graphics.GetNumberOfFrames(sm_displayedAnimationID))
            {
                sm_currentFrame = 0;
            }
        }
        ImGui::Image((void*)sm_viewAnimation, ImVec2(256, 256));
        ImGui::End();
    }
    ImGui::End();
}

void UserInterface::RenderedObjectInterface(ID3D11Device* device)
{
    ImGui::Begin("Create Rendered Object");
    ImGui::Text("Non Animated Render Creation");
    ImGui::InputInt("QuadID###nonAnimQuad", &sm_quadToAttatch);
    ImGui::InputInt("TextureID###createTexture", &sm_textureToAttach);
    if (ImGui::Button("Create Non Animated"))
    {
        sm_resultRenderObjectCreation = m_graphics.CreateRenderObject(sm_quadToAttatch, sm_textureToAttach);
    }
    ImGui::Text(sm_resultRenderObjectCreation.c_str());

    ImGui::Text(" ");
    ImGui::Text("Animated Render Creation");
    ImGui::InputInt("QuadID###animAquad", &sm_quadToAttatch);
    ImGui::InputInt("AnimationID###createAnim", &sm_aniamtionToAttatch);
    ImGui::InputFloat("FrameTime###createFramTime", &sm_animationTimer);
    if (ImGui::Button("Create Animated"))
    {
        sm_resultRenderObjectAnimationCreation = m_graphics.CreateAnimatedRenderObject(sm_quadToAttatch, sm_aniamtionToAttatch,sm_animationTimer);
    }
    ImGui::Text(sm_resultRenderObjectAnimationCreation.c_str());

    ImGui::Text(" ");
    ImGui::Text("Add Animation To Render Object");
    ImGui::InputInt("RenderObjectID###add", &sm_renderedObjectID);
    ImGui::InputInt("AnimationID###selectAnim", &sm_aniamtionToAttatch);
    ImGui::InputFloat("FrameTime###addFrameTime", &sm_animationTimer);
    if (ImGui::Button("Add Animation"))
    {
        sm_resultAddAnimation = m_graphics.AddAnimationToRenderObject(sm_renderedObjectID, sm_aniamtionToAttatch, sm_animationTimer);
    }
    ImGui::Text(sm_resultAddAnimation.c_str());

    ImGui::Text(" ");
    ImGui::Text("Remove Animation From Render Object");
    ImGui::InputInt("RenderObjectID###remove", &sm_renderedObjectID);
    ImGui::InputInt("InternalAnimationID###selectAnimRemove", &sm_aniamtionInternal);
    if (ImGui::Button("Remove Animation"))
    {
        sm_resultRemoveAnimation = m_graphics.RemoveAnimationFromRenderObject(sm_renderedObjectID, sm_aniamtionToAttatch);
    }
    ImGui::Text(sm_resultRemoveAnimation.c_str());

    ImGui::Text(" ");
    ImGui::Text("Change Current Animation");
    ImGui::InputInt("RenderObjectID###change", &sm_renderedObjectID);
    ImGui::InputInt("InternalAnimationID###selectAnimCurrent", &sm_aniamtionInternal);
    if (ImGui::Button("Update Current Animation"))
    {
        sm_resultUpdateCurrentAnimation = m_graphics.GetSpecificRenderObject(sm_renderedObjectID)->SetCurrentAnimation(sm_aniamtionInternal);
    }
    ImGui::Text(sm_resultUpdateCurrentAnimation.c_str());
    ImGui::Text(" ");
    ImGui::Text("Delete Render Object (Warning may crash if in use)");
    ImGui::InputInt("RenderObjectID###delete", &sm_renderedObjectID);
    if (ImGui::Button("Delete Rendered (Warning may crash if in use)"))
    {
        sm_resultDeleteRenderedObject = m_graphics.DeleteRenderedObject(sm_renderedObjectID);

    }
    ImGui::Text(sm_resultDeleteRenderedObject.c_str());

    ImGui::Text(" ");
    ImGui::Text("Display Rendered Object Info");
    ImGui::InputInt("RenderObjectID###display", &sm_renderedObjectID);
    ImGui::Checkbox("Open Display Window",&sm_toggleDisplayRenderedObject);
    if (ImGui::Button("Display"))
    {
        sm_renderedObjectExists = m_graphics.GetSpecificRenderObject(sm_renderedObjectID);
        if (sm_renderedObjectExists)
        {
            sm_renderedObject = m_graphics.GetSpecificRenderObject(sm_renderedObjectID);
            sm_displayedRenderObjectID = sm_renderedObjectID;

        }
    }
    if (sm_toggleDisplayRenderedObject && sm_renderedObjectExists)
    {
        sm_viewRenderedObject = m_graphics.GetSpecificRenderObject(sm_displayedRenderObjectID)->GetTexture(sm_renderedObject->GetCurrentAnimation(), sm_renderedObject->GetCurrentFrame());
        ImGui::Begin("Display Rendered Object");
        std::string id = "Displaying Rendered Object: " + std::to_string(sm_displayedRenderObjectID);
        std::string number = "Number of animations : " + std::to_string(sm_renderedObject->GetAnimations().size());
        ImGui::Text(id.c_str());
        ImGui::Text(number.c_str());
        ImGui::Image((void*)sm_viewRenderedObject, ImVec2(256, 256));
        ImGui::End();
    }

    ImGui::End();
}

void UserInterface::GameObjectInterface(ID3D11Device* device, std::vector<GameObject*>& gameObjects)
{
    ImGui::Begin("Game Object Management");
    ImGui::Text("Create a Game Object");
    ImGui::InputFloat3("Position", sm_positionCreation,1);
    ImGui::InputFloat2("Scale###original", sm_scaleCreation,1);
    ImGui::InputFloat3("Rotation", sm_rotationCreation, 1);
    ImGui::InputInt("RenderObjectID", &sm_renderedObjectAttatch);
    if (ImGui::Button("Create Object"))
    {
        GameObject* newObj = new GameObject(sm_positionCreation[0], sm_positionCreation[1], sm_positionCreation[2],
            sm_scaleCreation[0], sm_scaleCreation[1], sm_rotationCreation[0], sm_rotationCreation[1], sm_rotationCreation[2]);
        if (sm_renderedObjectAttatch < 0 || sm_renderedObjectAttatch >= m_graphics.GetObjectsToRender().size())
        {
            sm_resultGameObjectCreation = "Object created in slot: " + std::to_string(gameObjects.size() - 1) + "\nNo Render attatched";
        }
        else
        {
            newObj->SetRenderObject(m_graphics.GetSpecificRenderObject(sm_renderedObjectAttatch));
            sm_resultGameObjectCreation = "Object created in slot: " + std::to_string(gameObjects.size() - 1);
        }
        gameObjects.push_back(newObj);
    }
    ImGui::Text(sm_resultGameObjectCreation.c_str());


    ImGui::Text("");
    ImGui::Text("Edit Game Object");
    if (ImGui::InputInt("ID###ObjectToEdit", &sm_selectedGameObject))
    {
        bool functional = true;
        try {
            gameObjects.at(sm_selectedGameObject);
        }
        catch (const std::out_of_range & e)
        {
            functional = false;
            sm_resultMoveObject = "Enter a valid ID";
        }
        if (functional)
        {
            sm_editingEnabled = true;
            sm_editingGameObject = sm_selectedGameObject;
            sm_resultMoveObject = "Object " + std::to_string(sm_editingGameObject) + " selected" ;
            DirectX::XMFLOAT3 pos = gameObjects[sm_editingGameObject]->GetPosition();
            sm_currentPosition[0] = pos.x; sm_currentPosition[1] = pos.y; sm_currentPosition[2] = pos.z;
            DirectX::XMFLOAT2 scale = gameObjects[sm_editingGameObject]->GetScale();
            sm_currentScale[0] = scale.x; sm_currentScale[1] = scale.y;
            DirectX::XMFLOAT3 rot = gameObjects[sm_editingGameObject]->GetRotation();
            sm_currentRotation[0] = rot.x; sm_currentRotation[1] = rot.y; sm_currentRotation[2] = rot.z;
        }
    }
    ImGui::DragFloat3("Pos", sm_currentPosition,1.f,-100000,100000);
    ImGui::DragFloat2("Scale###adjust", sm_currentScale, 1.f, 0, 1000);
    ImGui::DragFloat3("rot", sm_currentRotation, 0.05f, -3.142f, 3.142f);
    if (sm_editingEnabled)
    {
        gameObjects[sm_editingGameObject]->SetPosition(sm_currentPosition[0], sm_currentPosition[1], sm_currentPosition[2]);
        gameObjects[sm_editingGameObject]->SetScale(sm_currentScale[0], sm_currentScale[1]);
        gameObjects[sm_editingGameObject]->SetRotation(sm_currentRotation[0], sm_currentRotation[1], sm_currentRotation[2]);
    }
    ImGui::Text("New Render");
    if (ImGui::InputInt("ID###RenderObj", &sm_renderedObjectAttatch) && sm_editingEnabled)
    {
        if (sm_renderedObjectAttatch < 0 || sm_renderedObjectAttatch >= m_graphics.GetObjectsToRender().size())
        {
            sm_resultMoveObject = "Object " + std::to_string(sm_editingGameObject) + " selected\nRender Object outside vector";
        }
        else
        {
            sm_resultMoveObject = "Object " + std::to_string(sm_editingGameObject) + " selected";
            gameObjects[sm_editingGameObject]->SetRenderObject(m_graphics.GetSpecificRenderObject(sm_renderedObjectAttatch));
        }
    }
    ImGui::Text(sm_resultMoveObject.c_str());

    ImGui::Text("");     ImGui::Text("");     ImGui::Text("");
    ImGui::InputText("SaveFile",sm_saveFile,255);
    if (ImGui::Button("SAVE"))
    {

    }
    ImGui::End();
}
