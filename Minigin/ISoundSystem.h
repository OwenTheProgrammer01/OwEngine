#pragma once
#include <memory>
#include <string>

namespace dae
{
	using Sound = std::string;

	class ISoundSystem abstract
	{
	public:
		ISoundSystem() = default;
		virtual ~ISoundSystem() = default;

		virtual void PlaySound(Sound sound, int volume) = 0;
		virtual void SetVolumeAllSounds(int volume) = 0;
		virtual void MuteSound(Sound sound, bool mute) = 0;
		virtual void MuteAllSounds(bool mute) = 0;
		virtual void StopSound(Sound sound) = 0;
		virtual void StopAllSounds() = 0;

		ISoundSystem(const ISoundSystem& other) = delete;
		ISoundSystem(ISoundSystem&& other) = delete;
		ISoundSystem& operator=(const ISoundSystem& other) = delete;
		ISoundSystem& operator=(ISoundSystem&& other) = delete;
	};
}