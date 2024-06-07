#include "EventManager.h"

void dae::EventManager::ProcessEventQueue()
{
	while (not m_EventQueue.empty())
	{
		HandleEvent(m_EventQueue.front().get());
		m_EventQueue.pop();
	}
}

void dae::EventManager::PlaceEventOnQueue(std::unique_ptr<Event> event)
{
	m_EventQueue.emplace(std::move(event));
}

void dae::EventManager::RemoveEvent(const std::string& eventName)
{
	m_EventCallbacks.erase(eventName);
}

void dae::EventManager::RegisterObserver(std::weak_ptr<Observer> pObserver, fEventCallback fCallback, const std::string& eventName)
{
	auto& CreateObserver{ m_EventCallbacks[eventName] };
	CreateObserver.emplace_back(pObserver, fCallback);
}

void dae::EventManager::HandleEvent(Event* event)
{
	const auto& eventName{ event->GetEventName() };

	auto it{ m_EventCallbacks.find(eventName) };

	if (it != m_EventCallbacks.end())
	{
		auto& ObserverCallback{ it->second };

		std::erase_if(ObserverCallback, [](const auto& pair)
			{
				return pair.first.expired();
			});

		for (const auto& [pObserver, fCallback] : ObserverCallback)
		{
			fCallback(*event);
		}

		return;
	}
}