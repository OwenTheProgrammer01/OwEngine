#pragma once
#include <memory>

//#include "XInput.h"

//class Command;
//enum class InputState;

namespace dae
{
    class ControllerInput
    {
    public:
        ControllerInput();
        ~ControllerInput() = default;

        //void ProcessInputState();
        //void ProcessMappedActions();
        //void MapActionToInput(unsigned int key, InputState inputState, std::shared_ptr<Command> pInputAction);

        ControllerInput(const ControllerInput&) = delete;
        ControllerInput(ControllerInput&&) = delete;
        ControllerInput& operator=(const ControllerInput&) = delete;
        ControllerInput& operator=(const ControllerInput&&) = delete;

    private:
        //bool IsDownThisFrame(unsigned int button) const { return m_ButtonsPressedThisFrame & button; }
        //bool IsUpThisFrame(unsigned int button) const { return m_ButtonsReleasedThisFrame & button; }
        //bool IsPressed(unsigned int button) const { return m_CurrentState.Gamepad.wButtons & button; }
    };
}