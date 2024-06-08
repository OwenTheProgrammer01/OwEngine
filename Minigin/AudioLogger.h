#pragma once
#include "ISoundSystem.h"
#include <iostream>

namespace dae
{
	class LoggedAudio : public ISoundSystem
	{
	public:
		LoggedAudio(ISoundSystem& wrapped)
			: m_Wrapped(wrapped)
		{}

		void PlaySound(SoundID soundID, int volume) override
		{
			Log("Play sound");
			m_Wrapped.PlaySound(soundID, volume);
		}

		void MuteSound(SoundID soundID, bool mute) override
		{
			Log("Mute sound");
			m_Wrapped.MuteSound(soundID, mute);
		}

		void MuteAllSounds(bool mute) override
		{
			Log("Mute all sounds");
			m_Wrapped.MuteAllSounds(mute);
		}

		void StopSound(SoundID soundID) override
		{
			Log("Stop sound");
			m_Wrapped.StopSound(soundID);
		}

		void StopAllSounds() override
		{
			Log("Stop all sounds");
			m_Wrapped.StopAllSounds();
		}
	private:
		void Log(const char* message)
		{
			// Code to log message...
			std::cout << message << std::endl;
		}

		ISoundSystem& m_Wrapped;
	};
}