#pragma once
#include "Audio.h"
#include <variant>

class Sound
{
public:

	Sound();
	~Sound();
	void Update(float elapsedTime);
	void OnSuspending();
	void OnResuming();
	void Load(wchar_t * file,int id);
	void Play(int id);
	void PlayLoop(int id);
	void Stop(int id);
	void SetVolume(int volume, int id);
	void SetPan(int pan, int id);

	std::unique_ptr<DirectX::AudioEngine> m_audEngine;
	std::vector<std::unique_ptr<DirectX::SoundEffect>> m_soundTemp;
	std::vector<std::unique_ptr<DirectX::SoundEffectInstance>> m_soundVector;

};

