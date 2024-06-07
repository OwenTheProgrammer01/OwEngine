#include "SoundSystem.h"

class dae::SoundSystem::SDL_MixerImpl
{
public:
	SDL_MixerImpl();
	~SDL_MixerImpl() = default;


private:

};

dae::SoundSystem::SDL_MixerImpl::SDL_MixerImpl()
{}

dae::SoundSystem::SoundSystem()
	: pImpl{ std::make_unique<SDL_MixerImpl>() }
{}

dae::SoundSystem::~SoundSystem() = default;