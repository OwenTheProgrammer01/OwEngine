#pragma once
#include <memory>
#include <queue>
#include <string>

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

        void BroadcastEvent(std::unique_ptr<Event> event);
        void BroadcastBlockingEvent(std::unique_ptr<Event> event);

        //std::shared_ptr<Observer> CreateObserver() const { return std::make_shared<Observer>(); }

        void RemoveEvent(const std::string& eventName);

        EventManager(const EventManager&) = delete;
        EventManager(EventManager&&) = delete;
        EventManager& operator=(const EventManager&) = delete;
        EventManager& operator=(const EventManager&&) = delete;
    private:
        friend class Singleton<EventManager>;

        friend class Observer;
        using fCallback = std::function<void(const Event&)>;
        void RegisterObserver(std::weak_ptr<Observer> pObserver, fCallback fCallback, const std::string& eventName);
        void ProcessEvent(std::unique_ptr<Event> event);
        //void ProcessEvent(Event* event);

        using ObserverCallback = std::vector<std::pair<std::weak_ptr<Observer>, fCallback>>;
        std::map<std::string, ObserverCallback> m_EventCallbacks;

        std::queue<std::unique_ptr<Event>> m_EventQueue;
    };
}