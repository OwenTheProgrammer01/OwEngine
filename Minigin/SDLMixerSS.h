#pragma once
#include "ISoundSystem.h"

namespace dae
{
	class SDLMixerSS final : public ISoundSystem
	{
	public:
		SDLMixerSS();
		virtual ~SDLMixerSS() override;

		void PlaySound(Sound sound, int volume) override;
		void SetVolumeAllSounds(int volume) override;
		void MuteSound(Sound sound, bool mute) override;
		void MuteAllSounds(bool mute) override;
		void StopSound(Sound sound) override;
		void StopAllSounds() override;

		SDLMixerSS(const SDLMixerSS& other) = delete;
		SDLMixerSS(SDLMixerSS&& other) = delete;
		SDLMixerSS& operator=(const SDLMixerSS& other) = delete;
		SDLMixerSS& operator=(SDLMixerSS&& other) = delete;
	private:
		class SDLImpl;
		std::unique_ptr<SDLImpl> m_Impl;
	};
}