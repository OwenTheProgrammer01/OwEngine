#pragma once
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

    class Controller final : public Device
    {
    public:
        Controller(int userIndex);
        virtual ~Controller() override;
        
        void ProcessInput() override;
        
        Controller(const Controller&) = delete;
        Controller(Controller&&) = delete;
        Controller& operator=(const Controller&) = delete;
        Controller& operator=(const Controller&&) = delete;
        
    private:
        int m_UserIndex;
        
        class ControllerImpl;
        std::unique_ptr<ControllerImpl> m_pImpl;
        
        int GetKeyCode(int key) const;
        bool IsDownThisFrame(int btn) const;
        bool IsUpThisFrame(int btn) const;
        bool IsPressed(int btn) const;
    };
}