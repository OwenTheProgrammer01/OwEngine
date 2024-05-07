#pragma once
#include "Device.h"

namespace dae
{
    enum class ControllerButton
    {
        //--- Digital ---
        DPadUp,		// (Xbox) --> Up Arrow (Playstation)
        DPadDown,	// (Xbox) --> Down Arrow (Playstation)
        DPadLeft,	// (Xbox) --> Left Arrow (Playstation)
        DPadRight,	// (Xbox) --> Right Arrow (Playstation)

        Start,	// (Xbox) --> Options (Playstation)
        Back,	// (Xbox) --> Share (Playstation)

        LeftThumb,	// (Xbox) --> LeftThumb (Playstation)
        RightThumb,	// (Xbox) --> RightThumb (Playstation)

        LeftShoulder,	// (Xbox) --> LeftShoulder (Playstation)
        RightShoulder,	// (Xbox) --> RightShoulder (Playstation)

        A, // (Xbox) --> Cross (Playstation)
        B, // (Xbox) --> Circle (Playstation)
        X, // (Xbox) --> Square (Playstation)
        Y, // (Xbox) --> Triangle (Playstation)
        //--- Digital ---

        //--- Analog ---
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