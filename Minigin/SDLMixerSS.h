#pragma once
#include <map>
#include <string>
#include "ISoundSystem.h"

namespace dae
{
	class SDLMixerSS final : public ISoundSystem
	{
	public:
		SDLMixerSS();
		~SDLMixerSS() override;

		void PlaySound(SoundData soundData, int volume) override;
		void SetVolumeAllSounds(int volume) override;
		void MuteSound(SoundData soundData, bool mute) override;
		void MuteAllSounds(bool mute) override;
		void StopSound(SoundData soundData) override;
		void StopAllSounds() override;
	private:
		class SDLImpl;
		std::unique_ptr<SDLImpl> m_Impl;
	};
}