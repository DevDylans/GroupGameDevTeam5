//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "debugapi.h"

extern void ExitGame();

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

Game::~Game()
{

}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    CollisionManager::Create();

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    m_LevelFile = LevelFile();

    m_LevelFile.ReadTextureFile();
    for (int i = 0; i < m_LevelFile.GetTextures().size(); i = i++)
    {
        m_graphicsComponenet->CreateTexture(m_deviceResources->GetD3DDevice(), m_LevelFile.GetTextures()[i]);
    }
    m_LevelFile.ReadRenderedObjectFile();
    for (int i = 0; i < m_LevelFile.GetRenderedObjects().size(); i = i + 3)
    {
        m_graphicsComponenet->CreateAnimatedRenderObject(m_LevelFile.GetRenderedObjects()[i], m_LevelFile.GetRenderedObjects()[i + 1], m_LevelFile.GetRenderedObjects()[i + 2]);
    }
    m_LevelFile.ReadLevelFile();
    for (int i = 0; i < m_LevelFile.GetGameObjects().size(); i = i++)
    {
        m_LevelFile.GetGameObjects()[i]->SetRenderObject(m_graphicsComponenet->GetSpecificRenderObject(m_LevelFile.GetRenderIDs()[i]));
    }

    CreateWindowSizeDependentResources();
    m_UI = new UserInterface(window, m_deviceResources->GetD3DDevice(), m_deviceResources->GetD3DDeviceContext(), *m_graphicsComponenet, m_LevelFile);

    m_sound = new Sound();
    m_sound->Load(L"death.wav",0);
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;
    m_graphicsComponenet->Update(elapsedTime);

    CollisionManager::GetInstance()->CollisionDetection();

    CollisionManager::GetInstance()->UpdatePhysics(elapsedTime);
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    context;
    //m_deviceResources->GetD3DDeviceContext()->OMSetDepthStencilState
    m_graphicsComponenet->Draw(context,0, m_LevelFile.GetGameObjects());
    m_UI->Draw(m_deviceResources->GetD3DDevice(), m_LevelFile.GetGameObjects());
    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
    m_sound->OnSuspending();
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
    m_sound->OnResuming();
}

void Game::OnWindowMoved()
{
    auto r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 1600;
    height = 900;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;

    m_graphicsComponenet = new Graphics(device);
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
    //bubblesort
    int size = m_LevelFile.GetGameObjects().size();
    bool swapped = false;
    for (int i = 0; i < size; i++)
    {
        swapped = false;
        for (int j = 0; j < (size - i) - 1; j++)
        {
            if (m_LevelFile.GetGameObjects()[j]->GetTransform().GetPosition().z < m_LevelFile.GetGameObjects()[j + 1]->GetTransform().GetPosition().z)
            {
                GameObject* temp = nullptr;
                temp = m_LevelFile.GetGameObjects()[j];
                m_LevelFile.GetGameObjects()[j] = m_LevelFile.GetGameObjects()[j + 1];
                m_LevelFile.GetGameObjects()[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }


}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

    CollisionManager::Destroy();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
