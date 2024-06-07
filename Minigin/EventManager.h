#pragma once
#include <queue>
#include <map>
#include <functional>

#include "Singleton.h"
#include "Event.h"
#include "Observer.h"

namespace dae
{
    class EventManager final : public Singleton<EventManager>
    {
    public:
        EventManager() = default;
        ~EventManager() = default;

        void ProcessEventQueue();

        void PlaceEventOnQueue(std::unique_ptr<Event> event);
        void RemoveEvent(const std::string& eventName);

        EventManager(const EventManager&) = delete;
        EventManager(EventManager&&) = delete;
        EventManager& operator=(const EventManager&) = delete;
        EventManager& operator=(const EventManager&&) = delete;
    private:
        friend class Singleton<EventManager>;

        friend class Observer;
        using fEventCallback = std::function<void(const Event&)>;
        void RegisterObserver(std::weak_ptr<Observer> pObserver, fEventCallback fCallback, const std::string& eventName);
        void HandleEvent(Event* event);

        using ObserverCallback = std::vector<std::pair<std::weak_ptr<Observer>, fEventCallback>>;
        std::map<std::string, ObserverCallback> m_EventCallbacks;

        std::queue<std::unique_ptr<Event>> m_EventQueue;
    };
}