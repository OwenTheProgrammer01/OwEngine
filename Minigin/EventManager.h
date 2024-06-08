#pragma once
#include <memory>
#include <queue>
#include <map>
#include <functional>

#include "Singleton.h"
#include "Event.h"

namespace dae
{
    using EventHandler = std::function<void()>;

    class EventManager final : public Singleton<EventManager>
    {
    public:

        virtual ~EventManager() = default;

        void ProcessEventQueue();

        void AddEventOnQueue(std::unique_ptr<Event> pEvent);
        void RemoveEvent(const std::string& eventName);

        void RegisterHandler(const std::string& eventName, EventHandler handler);

        EventManager(const EventManager&) = delete;
        EventManager(EventManager&&) = delete;
        EventManager& operator=(const EventManager&) = delete;
        EventManager& operator=(const EventManager&&) = delete;
    private:
        friend class Singleton<EventManager>;
        EventManager() = default;

        void HandleEvent(Event* pEvent);

        std::map<std::string, EventHandler> m_EventHandlers;

        std::queue<std::unique_ptr<Event>> m_EventQueue;
    };
}