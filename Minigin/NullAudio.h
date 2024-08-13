#pragma once
#include "ISoundSystem.h"

namespace dae
{
	class NullAudio final : public ISoundSystem
	{
	public:
		NullAudio() = default;
		~NullAudio() override = default;

		void PlaySound(Sound sound, int volume) override { sound; volume; /* Do nothing. */ }
		void SetVolumeAllSounds(int volume) override { volume; /* Do nothing */ };
		void MuteSound(Sound sound, bool mute) override { sound; mute; /* Do nothing. */ }
		void MuteAllSounds(bool mute) override { mute; /* Do nothing. */ }
		void StopSound(Sound sound) override { sound; /* Do nothing. */ }
		void StopAllSounds() override { /* Do nothing. */ }
	};
}