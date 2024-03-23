#pragma once
#include <memory>

#include "Action.h"

namespace dae
{
    enum class KeyState
    {
        UpThisFrame,
        DownThisFrame,
        Pressed
    };

    class Device abstract
    {
    public:
        Device() = default;
        virtual ~Device() = default;

        virtual void ProcessInput() = 0;
        virtual void BindActionToKey(unsigned int key, KeyState keyState, std::shared_ptr<Action> pAction) = 0;

        Device(const Device&) = delete;
        Device(Device&&) = delete;
        Device& operator=(const Device&) = delete;
        Device& operator=(const Device&&) = delete;

    private:
        virtual unsigned int GetKeyCode(unsigned int key) const = 0;
        virtual bool IsDownThisFrame(unsigned int btn) const = 0;
        virtual bool IsUpThisFrame(unsigned int btn) const = 0;
        virtual bool IsPressed(unsigned int btn) const = 0;
    };
}
