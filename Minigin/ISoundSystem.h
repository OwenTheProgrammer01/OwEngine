#pragma once
#include <memory>
#include <string>

namespace dae
{
	using SoundID = unsigned short;

	struct SoundData
	{
		SoundID ID;
		std::string filePath;
	};

	class ISoundSystem abstract
	{
	public:
		ISoundSystem() = default;
		virtual ~ISoundSystem() = default;

		virtual void PlaySound(SoundData soundData, int volume) = 0;
		virtual void SetVolumeAllSounds(int volume) = 0;
		virtual void MuteSound(SoundData soundData, bool mute) = 0;
		virtual void MuteAllSounds(bool mute) = 0;
		virtual void StopSound(SoundData soundData) = 0;
		virtual void StopAllSounds() = 0;

		ISoundSystem(const ISoundSystem& other) = delete;
		ISoundSystem(ISoundSystem&& other) = delete;
		ISoundSystem& operator=(const ISoundSystem& other) = delete;
		ISoundSystem& operator=(ISoundSystem&& other) = delete;
	};
}