#pragma once
#include <memory>
#include <map>
#include "Action.h"

namespace dae
{
    enum class Keys;
    enum class Buttons;

    enum class State
    {
        //--- States ---
        IsPressed,	            // Key or button is pressed
        IsPressedThisFrame,		// Key or button is pressed this frame
        IsReleasedThisFrame     // Key or button is released this frame
    };


    class Device abstract
    {
    public:
        Device() = default;
        virtual ~Device() = default;

        virtual void ProcessInput() = 0;

        virtual void ProcessActions(std::map<State, std::map<Keys, std::shared_ptr<Action>>> keyboardCommands) {};
        virtual void ProcessActions(std::map<State, std::map<Buttons, std::shared_ptr<Action>>> controllerCommands) {};

        Device(const Device&) = delete;
        Device(Device&&) = delete;
        Device& operator=(const Device&) = delete;
        Device& operator=(const Device&&) = delete;
    };
}