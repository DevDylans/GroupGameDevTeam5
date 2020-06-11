#include "pch.h"
#include "Sound.h"
#include <windows.h>
#include <Mmsystem.h>
#include <Dsound.h>

using namespace DirectX;

Sound::Sound()
{
    AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
    eflags = eflags | AudioEngine_Debug;
#endif
    m_audEngine = std::make_unique<AudioEngine>(eflags);

}

Sound::~Sound()
{
    if (m_audEngine)
    {
        m_audEngine->Suspend();
    }

    for (int i = 0; i < m_soundVector.size(); i++)
    {
        m_soundVector[i].reset();
    }
}

void Sound::Update(float elapsedTime) 
{

}

void Sound::OnSuspending()
{
    m_audEngine->Suspend();
}

void Sound::OnResuming()
{
    m_audEngine->Resume();
}

void Sound::Load(wchar_t* file, int id)
{
    m_soundTemp.push_back(std::make_unique<SoundEffect>(m_audEngine.get(), file));
    m_soundVector.push_back(m_soundTemp[id]->CreateInstance());
}

void Sound::Play(int id)
{
    m_soundVector[id]->Play();
}

void Sound::PlayLoop(int id)
{
    m_soundVector[id]->Play(true);
}

void Sound::Stop(int id) 
{
    m_soundVector[id]->Stop();
}

void Sound::SetVolume(int volume, int id) 
{
    m_soundVector[id]->SetVolume(volume);
}

void Sound::SetPan(int pan, int id) 
{
    m_soundVector[id]->SetPan(pan);
}


