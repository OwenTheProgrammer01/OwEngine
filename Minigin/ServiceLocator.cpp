#include "ServiceLocator.h"

std::unique_ptr<dae::ISoundSystem> dae::ServiceLocator::m_Service{ std::make_unique<dae::NullAudio>() };