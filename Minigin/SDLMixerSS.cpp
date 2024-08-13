#include "SDLMixerSS.h"

#include <unordered_map>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <SDL_mixer.h>
#include "ISoundSystem.h"

//TODO: Fix this SoundSystem implementation

class dae::SDLMixerSS::SDLImpl
{
public:
    SDLImpl();
    ~SDLImpl();

    void PlaySound(Sound sound, int volume);
    void SetVolumeAllSounds(int volume);
    void MuteSound(Sound sound, bool mute);
    void MuteAllSounds(bool mute);
    void StopSound(Sound sound);
    void StopAllSounds();
private:
    std::unordered_map<Sound, Mix_Chunk*> m_Sounds;
    std::unordered_map<Sound, int> m_SoundChannels;
    std::queue<Sound> m_LoadQueue;
    int m_MasterVolume;
    bool m_AllMuted;

    std::mutex m_QueueMutex;
    std::condition_variable m_QueueCondition;
    std::jthread m_LoadThread;
    bool m_ExitThread;

    Mix_Chunk* GetChunk(Sound sound);
    void LoadSound(Sound sound);
    void ProcessQueue();
};

dae::SDLMixerSS::SDLImpl::SDLImpl() : m_MasterVolume(MIX_MAX_VOLUME), m_AllMuted(false), m_ExitThread(false)
{
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0)
    {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }

    m_LoadThread = std::jthread([this](std::stop_token stoken) {
        while (!stoken.stop_requested())
        {
            ProcessQueue();
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Polling interval
        }
        });
}

dae::SDLMixerSS::SDLImpl::~SDLImpl()
{
    {
        std::lock_guard<std::mutex> lock(m_QueueMutex);
        m_ExitThread = true;
    }
    m_QueueCondition.notify_all();
}

void dae::SDLMixerSS::SDLImpl::PlaySound(Sound sound, int volume)
{
    Mix_Chunk* chunk = GetChunk(sound);
    if (chunk)
    {
        int channel = Mix_PlayChannel(-1, chunk, 0);
        if (channel != -1)
        {
            Mix_Volume(channel, m_AllMuted ? 0 : volume);
            m_SoundChannels[sound] = channel;
        }
    }
    else
    {
        // If the chunk is not available, queue it for loading
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_LoadQueue.push(sound);
        }
        m_QueueCondition.notify_one();
    }
}

void dae::SDLMixerSS::SDLImpl::SetVolumeAllSounds(int volume)
{
    m_AllMuted = false;
    m_MasterVolume = volume;
    Mix_Volume(-1, m_MasterVolume);
}

void dae::SDLMixerSS::SDLImpl::MuteSound(Sound sound, bool mute)
{
    auto it = m_SoundChannels.find(sound);
    if (it != m_SoundChannels.end())
    {
        Mix_Volume(it->second, mute ? 0 : m_MasterVolume);
    }
}

void dae::SDLMixerSS::SDLImpl::MuteAllSounds(bool mute)
{
    m_AllMuted = mute;
	Mix_Volume(-1, mute ? 0 : m_MasterVolume);
}

void dae::SDLMixerSS::SDLImpl::StopSound(Sound sound)
{
    auto it = m_SoundChannels.find(sound);
    if (it != m_SoundChannels.end())
    {
        Mix_HaltChannel(it->second);
        m_SoundChannels.erase(it);
    }
}

void dae::SDLMixerSS::SDLImpl::StopAllSounds()
{
    Mix_HaltChannel(-1);
    m_SoundChannels.clear();
}

void dae::SDLMixerSS::SDLImpl::ProcessQueue()
{
    std::unique_lock<std::mutex> lock(m_QueueMutex);
    m_QueueCondition.wait(lock, [this] { return !m_LoadQueue.empty() || m_ExitThread; });

    while (!m_LoadQueue.empty())
    {
        Sound sound = m_LoadQueue.front();
        m_LoadQueue.pop();
        lock.unlock();
        LoadSound(sound);
        lock.lock();
    }
}

Mix_Chunk* dae::SDLMixerSS::SDLImpl::GetChunk(Sound sound)
{
    auto it = m_Sounds.find(sound);
    if (it != m_Sounds.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void dae::SDLMixerSS::SDLImpl::LoadSound(Sound sound)
{
    std::string fullpath = "../Data/Sounds/" + sound;
    Mix_Chunk* chunk = Mix_LoadWAV(fullpath.c_str());
    if (chunk)
    {
        m_Sounds[sound] = chunk;
    }
    else
    {
        std::cerr << "Failed to load sound " << fullpath << "! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

dae::SDLMixerSS::SDLMixerSS() 
    : m_Impl(std::make_unique<SDLImpl>())
{}

dae::SDLMixerSS::~SDLMixerSS() = default;

void dae::SDLMixerSS::PlaySound(Sound sound, int volume)
{
	m_Impl->PlaySound(sound, volume);
}

void dae::SDLMixerSS::SetVolumeAllSounds(int volume)
{
	m_Impl->SetVolumeAllSounds(volume);
}

void dae::SDLMixerSS::MuteSound(Sound sound, bool mute)
{
	m_Impl->MuteSound(sound, mute);
}

void dae::SDLMixerSS::MuteAllSounds(bool mute)
{
	m_Impl->MuteAllSounds(mute);
}

void dae::SDLMixerSS::StopSound(Sound sound)
{
	m_Impl->StopSound(sound);
}

void dae::SDLMixerSS::StopAllSounds()
{
	m_Impl->StopAllSounds();
}