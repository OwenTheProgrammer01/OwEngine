#pragma once
#include <memory>

#include "Device.h"

namespace dae
{
    enum class ControllerButton
    {
        //--- Digital ---
        A, // (Xbox) --> Cross (Playstation)
        B, // (Xbox) --> Circle (Playstation)
        X, // (Xbox) --> Square (Playstation)
        Y, // (Xbox) --> Triangle (Playstation)

        DPadLeft,	// (Xbox) --> Left Arrow (Playstation)
        DPadRight,	// (Xbox) --> Right Arrow (Playstation)
        DPadUp,		// (Xbox) --> Up Arrow (Playstation)
        DPadDown,	// (Xbox) --> Down Arrow (Playstation)

        LeftShoulder,	// (Xbox) --> LeftShoulder (Playstation)
        RightShoulder,	// (Xbox) --> RightShoulder (Playstation)

        Start,	// (Xbox) --> Options (Playstation)
        Back,	// (Xbox) --> Share (Playstation)
        //--- Digital ---

        //--- Analog ---
        LeftThumb,	// (Xbox) --> LeftThumbStick (Playstation)
        RightThumb,	// (Xbox) --> RightThumbStick (Playstation)

        LeftTrigger,	// (Xbox) --> LeftTrigger (Playstation)
        RightTrigger	// (Xbox) --> RightTrigger (Playstation)
        //--- Analog ---
    };

    class ControllerImpl;
    class ControllerInput final : public Device
    {
    public:
        ControllerInput();
        ~ControllerInput() override = default;

        void ProcessInput() override;
        void BindActionToKey(unsigned int key, KeyState keyState, std::shared_ptr<Action> pAction) override;

        ControllerInput(const ControllerInput&) = delete;
        ControllerInput(ControllerInput&&) = delete;
        ControllerInput& operator=(const ControllerInput&) = delete;
        ControllerInput& operator=(const ControllerInput&&) = delete;

    private:
        std::unique_ptr<ControllerImpl> m_pImpl;

        unsigned int GetKeyCode(unsigned int key) const override;
        bool IsDownThisFrame(unsigned int btn) const override;
        bool IsUpThisFrame(unsigned int btn) const override;
        bool IsPressed(unsigned int btn) const override;
    };
}