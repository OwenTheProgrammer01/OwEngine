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

    void PlaySound(SoundData soundData, int volume);
    void SetVolumeAllSounds(int volume);
    void MuteSound(SoundData soundData, bool mute);
    void MuteAllSounds(bool mute);
    void StopSound(SoundData soundData);
    void StopAllSounds();
private:
    std::unordered_map<SoundID, Mix_Chunk*> m_Sounds;
    std::unordered_map<SoundID, int> m_SoundChannels;
    std::queue<SoundData> m_LoadQueue;
    int m_MasterVolume;
    bool m_AllMuted;

    std::mutex m_QueueMutex;
    std::condition_variable m_QueueCondition;
    std::jthread m_LoadThread;
    bool m_ExitThread;

    Mix_Chunk* GetChunk(SoundData soundData);
    void LoadSound(SoundData soundData);
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
    m_LoadThread.request_stop();

    for (auto& pair : m_Sounds)
    {
        Mix_FreeChunk(pair.second);
    }
    m_Sounds.clear();
    Mix_CloseAudio();
}

void dae::SDLMixerSS::SDLImpl::PlaySound(SoundData soundData, int volume)
{
    Mix_Chunk* chunk = GetChunk(soundData);
    if (chunk)
    {
        int channel = Mix_PlayChannel(-1, chunk, 0);
        if (channel != -1)
        {
            Mix_Volume(channel, m_AllMuted ? 0 : volume);
            m_SoundChannels[soundData.ID] = channel;
        }
    }
    else
    {
        // If the chunk is not available, queue it for loading
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_LoadQueue.push(soundData);
        }
        m_QueueCondition.notify_one();
    }
}

void dae::SDLMixerSS::SDLImpl::SetVolumeAllSounds(int volume)
{
    m_AllMuted = false;
    m_MasterVolume = volume;
    for (auto& pair : m_SoundChannels)
    {
        Mix_Volume(pair.second, m_MasterVolume);
    }
}

void dae::SDLMixerSS::SDLImpl::MuteSound(SoundData soundData, bool mute)
{
    auto it = m_SoundChannels.find(soundData.ID);
    if (it != m_SoundChannels.end())
    {
        Mix_Volume(it->second, mute ? 0 : m_MasterVolume);
    }
}

void dae::SDLMixerSS::SDLImpl::MuteAllSounds(bool mute)
{
    m_AllMuted = mute;
    SetVolumeAllSounds(mute ? 0 : m_MasterVolume);
}

void dae::SDLMixerSS::SDLImpl::StopSound(SoundData soundData)
{
    auto it = m_SoundChannels.find(soundData.ID);
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
        SoundData soundData = m_LoadQueue.front();
        m_LoadQueue.pop();
        lock.unlock();
        LoadSound(soundData);
        lock.lock();
    }
}

Mix_Chunk* dae::SDLMixerSS::SDLImpl::GetChunk(SoundData soundData)
{
    auto it = m_Sounds.find(soundData.ID);
    if (it != m_Sounds.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void dae::SDLMixerSS::SDLImpl::LoadSound(SoundData soundData)
{
    std::string fullpath = "../Data/Sounds/" + soundData.filePath;
    Mix_Chunk* chunk = Mix_LoadWAV(fullpath.c_str());
    if (chunk)
    {
        m_Sounds[soundData.ID] = chunk;
    }
    else
    {
        std::cerr << "Failed to load sound " << fullpath << "! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

dae::SDLMixerSS::SDLMixerSS() : m_Impl(std::make_unique<SDLImpl>()) {}

dae::SDLMixerSS::~SDLMixerSS() = default;

void dae::SDLMixerSS::PlaySound(SoundData soundData, int volume)
{
	m_Impl->PlaySound(soundData, volume);
}

void dae::SDLMixerSS::SetVolumeAllSounds(int volume)
{
	m_Impl->SetVolumeAllSounds(volume);
}

void dae::SDLMixerSS::MuteSound(SoundData soundData, bool mute)
{
	m_Impl->MuteSound(soundData, mute);
}

void dae::SDLMixerSS::MuteAllSounds(bool mute)
{
	m_Impl->MuteAllSounds(mute);
}

void dae::SDLMixerSS::StopSound(SoundData soundData)
{
	m_Impl->StopSound(soundData);
}

void dae::SDLMixerSS::StopAllSounds()
{
	m_Impl->StopAllSounds();
}