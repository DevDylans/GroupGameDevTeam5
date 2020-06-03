//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"

#include "Graphics.h"
#include "GameObject.h"
#include "LevelFile.h"
#include <iostream>
#include <string>
#include "UserInterface.h"
#include <algorithm>
#include "sound.h" 
#include "Audio.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game();
    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;
    Graphics* m_graphicsComponenet = nullptr;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

    //UI
    UserInterface* m_UI = nullptr;
    // Gameplay Objects
    std::vector<GameObject*> m_gameObjects;

    LevelFile m_LevelFile;
    bool time = true;

    Sound * m_sound;
};
