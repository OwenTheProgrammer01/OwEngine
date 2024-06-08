#pragma once
#include <memory>
#include "ISoundSystem.h"
#include "NullAudio.h"

namespace dae
{
	class ServiceLocator final
	{
	public:
		static ISoundSystem& GetSoundSystem() { return *m_Service; }
		static void RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& service)
		{
			m_Service = service ? std::move(service) : std::make_unique<NullAudio>();
		}
	private:
		static std::unique_ptr<ISoundSystem> m_Service;
	};
}