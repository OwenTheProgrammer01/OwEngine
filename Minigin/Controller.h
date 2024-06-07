#pragma once
#include <glm/glm.hpp>

#include "Device.h"

namespace dae
{
    enum class Buttons
    {
        //--- Digital ---
        Default         = 0x0000,   // (Xbox) --> (Playstation)

        DPadUp          = 0x0001,   // (Xbox) --> Up Arrow (Playstation)
        DPadDown        = 0x0002,   // (Xbox) --> Down Arrow (Playstation)
        DPadLeft        = 0x0004,   // (Xbox) --> Left Arrow (Playstation)
        DPadRight       = 0x0008,   // (Xbox) --> Right Arrow (Playstation)

        Start           = 0x0010,   // (Xbox) --> Options (Playstation)
        Back            = 0x0020,   // (Xbox) --> Share (Playstation)

        LeftThumb       = 0x0040,   // (Xbox) --> LeftThumb (Playstation)
        RightThumb      = 0x0080,   // (Xbox) --> RightThumb (Playstation)

        LeftShoulder    = 0x0100,   // (Xbox) --> LeftShoulder (Playstation)
        RightShoulder   = 0x0200,   // (Xbox) --> RightShoulder (Playstation)

        A               = 0x1000,   // (Xbox) --> Cross (Playstation)
        B               = 0x2000,   // (Xbox) --> Circle (Playstation)
        X               = 0x4000,   // (Xbox) --> Square (Playstation)
        Y               = 0x8000,   // (Xbox) --> Triangle (Playstation)
        //--- Digital ---

        //--- Analog ---
        LeftTrigger     ,   // (Xbox) --> LeftTrigger (Playstation)
        RightTrigger    ,   // (Xbox) --> RightTrigger (Playstation)

        LeftThumbStick  ,   // (Xbox) --> LeftThumbStick (Playstation)
        RightThumbStick ,   // (Xbox) --> RightThumbStick (Playstation)
        //--- Analog ---
    };

    class Controller final : public Device
    {
    public:
        Controller(int userIndex);
        virtual ~Controller() override;
        
        void ProcessInput() override;

        virtual void ProcessActions(std::map<State, std::map<Buttons, std::shared_ptr<Action>>> controllerCommands) override;

        Controller(const Controller&) = delete;
        Controller(Controller&&) = delete;
        Controller& operator=(const Controller&) = delete;
        Controller& operator=(const Controller&&) = delete;
    private:
        bool IsPressed(unsigned int button) const;
        bool IsPressedThisFrame(unsigned int button) const;
        bool IsReleasedThisFrame(unsigned int button) const;

        int m_UserIndex;
        
        class ControllerImpl;
        std::unique_ptr<ControllerImpl> m_pImpl;
    };
}