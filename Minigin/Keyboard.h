//#pragma once
//#include "Device.h"
//
//namespace dae
//{
//    enum class Keys
//    {
//        //--- Keys ---
//        Escape,
//        F1,
//        F2,
//        F3,
//        F4,
//        F5,
//        F6,
//        F7,
//        F8,
//        F9,
//        F10,
//        F11,
//        F12,
//        PrintScreen,
//        ScrollLock,
//        Pause,
//
//        //
//        Key1,
//        Key2,
//        Key3,
//        Key4,
//        Key5,
//        Key6,
//        Key7,
//        Key8,
//        Key9,
//        Key0,
//        //
//        //
//        Backspace,
//        Insert,
//        Home,
//        pageUp,
//
//        Tab,
//        Q,
//        W,
//        E,
//        R,
//        T,
//        Y,
//        U,
//        I,
//        O,
//        P,
//        //
//        //
//        //
//        Delete,
//        End,
//        Down,
//
//        CapsLock,
//        A,
//        S,
//        D,
//        F,
//        G,
//        H,
//        J,
//        K,
//        L,
//        //
//        //
//        Enter,
//
//        LeftShift,
//        Z,
//        X,
//        C,
//        V,
//        B,
//        N,
//        M,
//        //
//        //
//        //
//        RightShift,
//        Up,
//
//        LeftCtrl,
//        //
//        LeftAlt,
//        
//        Shift,
//        Ctrl,
//        RightCtrl,
//        Alt,
//        RightAlt,
//        PageDown,
//        Left,
//        Right,
//        NumPad0,
//        NumPad1,
//        NumPad2,
//        NumPad3,
//        NumPad4,
//        NumPad5,
//        NumPad6,
//        NumPad7,
//        NumPad8,
//        NumPad9,
//        Multiply,
//        Add,
//        Subtract,
//        Decimal,
//        Divide,
//        NumLock
//    };
//
//    class Keyboard final : public Device
//    {
//    public:
//        Keyboard(int userIndex);
//        virtual ~Keyboard() override;
//
//        void ProcessInput() override;
//
//        virtual void ProcessActions(std::map<State, std::map<Keys, std::shared_ptr<Action>>> keyboardCommands) override;
//
//        Keyboard(const Keyboard&) = delete;
//        Keyboard(Keyboard&&) = delete;
//        Keyboard& operator=(const Keyboard&) = delete;
//        Keyboard& operator=(const Keyboard&&) = delete;
//
//    private:
//        int m_UserIndex;
//
//        class KeyboardImpl;
//        std::unique_ptr<KeyboardImpl> m_pImpl;
//
//        unsigned int GetKeyCode(Keys key) const;
//        bool IsPressed(unsigned int key) const;
//        bool IsPressedThisFrame(unsigned int key) const;
//        bool IsReleasedThisFrame(unsigned int key) const;
//    };
//}