#pragma once
#include <memory>

namespace dae
{
	class SoundSystem final
	{
	public:
		SoundSystem();
		~SoundSystem();

		//functions

		SoundSystem(const SoundSystem& other) = delete;
		SoundSystem(SoundSystem&& other) = delete;
		SoundSystem& operator=(const SoundSystem& other) = delete;
		SoundSystem& operator=(SoundSystem&& other) = delete;
	private:
		//private functions


		//variables


		class SDL_MixerImpl;
		std::unique_ptr<SDL_MixerImpl> pImpl{};
	};
}