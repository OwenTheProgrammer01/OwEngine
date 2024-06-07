#include "EventManager.h"

void dae::EventManager::ProcessEventQueue()
{
	while (not m_EventQueue.empty())
	{
		HandleEvent(m_EventQueue.front().get());
		m_EventQueue.pop();
	}
}

void dae::EventManager::AddEventOnQueue(std::unique_ptr<Event> pEvent)
{
	m_EventQueue.emplace(std::move(pEvent));
}

void dae::EventManager::RemoveEvent(const std::string& eventName)
{
	m_EventHandlers.erase(eventName);
}

void dae::EventManager::RegisterHandler(const std::string& eventName, EventHandler handler)
{
	m_EventHandlers[eventName] = handler;
}

void dae::EventManager::HandleEvent(Event* pEvent)
{
	const auto& eventName{ pEvent->GetEventName() };

	if (m_EventHandlers.find(eventName) != m_EventHandlers.end()) 
	{
		m_EventHandlers[eventName]();
	}
}