#pragma once
#include "Device.h"

namespace dae
{
    enum class Buttons
    {
        //--- Digital ---
        DPadUp,		        // (Xbox) --> Up Arrow (Playstation)
        DPadDown,	        // (Xbox) --> Down Arrow (Playstation)
        DPadLeft,	        // (Xbox) --> Left Arrow (Playstation)
        DPadRight,          // (Xbox) --> Right Arrow (Playstation)

        Start,	            // (Xbox) --> Options (Playstation)
        Back,	            // (Xbox) --> Share (Playstation)

        LeftThumb,	        // (Xbox) --> LeftThumb (Playstation)
        RightThumb,	        // (Xbox) --> RightThumb (Playstation)

        LeftShoulder,	    // (Xbox) --> LeftShoulder (Playstation)
        RightShoulder,	    // (Xbox) --> RightShoulder (Playstation)

        A,                  // (Xbox) --> Cross (Playstation)
        B,                  // (Xbox) --> Circle (Playstation)
        X,                  // (Xbox) --> Square (Playstation)
        Y,                  // (Xbox) --> Triangle (Playstation)
        //--- Digital ---

        //--- Analog ---
        LeftTrigger,	    // (Xbox) --> LeftTrigger (Playstation)
        RightTrigger,	    // (Xbox) --> RightTrigger (Playstation)

        LeftThumbStick,     // (Xbox) --> LeftThumbStick (Playstation)
        RightThumbStick,    // (Xbox) --> RightThumbStick (Playstation)
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
        int m_UserIndex;
        
        class ControllerImpl;
        std::unique_ptr<ControllerImpl> m_pImpl;
        
        unsigned int GetButtonCode(Buttons button) const;
        bool IsPressed(unsigned int button) const;
        bool IsPressedThisFrame(unsigned int button) const;
        bool IsReleasedThisFrame(unsigned int button) const;
    };
}