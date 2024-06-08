#pragma once
#include "ISoundSystem.h"

namespace dae
{
	class NullAudio final : public ISoundSystem
	{
	public:
		void PlaySound(SoundData soundData, int volume) override { soundData; volume; /* Do nothing. */ }
		void SetVolumeAllSounds(int volume) override { volume; /* Do nothing */ };
		void MuteSound(SoundData soundData, bool mute) override { soundData; mute; /* Do nothing. */ }
		void MuteAllSounds(bool mute) override { mute; /* Do nothing. */ }
		void StopSound(SoundData soundData) override { soundData; /* Do nothing. */ }
		void StopAllSounds() override { /* Do nothing. */ }
	};
}