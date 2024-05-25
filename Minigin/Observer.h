#pragma once
#include <memory>
#include <string>
#include <functional>
#include <map>

namespace dae
{
	class Observer final
	{
	public:
		Observer() = default;
		~Observer() = default;

		Observer(const Observer&) = delete;
		Observer(Observer&&) = delete;
		Observer& operator=(const Observer&) = delete;
		Observer& operator=(const Observer&&) = delete;

		//void RegisterForEvent(std::weak_ptr<Observer> pObs, const std::string& eventName, std::function<void(const Event& event)> fCallback)
		//{
		//	EventManager::GetInstance().RegisterObserver(pObs, fCallback, eventName);
		//}
	};
}