#pragma once
#include <string>

namespace dae
{
	class Event
	{
	public:
		Event(const std::string& eventName) : m_EventName(eventName) {}
		~Event() = default;

		const std::string& GetEventName() const { return m_EventName; }

		Event(const Event&) = delete;
		Event(Event&&) = delete;
		Event& operator=(const Event&) = delete;
		Event& operator=(const Event&&) = delete;
	private:
		const std::string m_EventName;
	};
}