#pragma once
#include "Device.h"

namespace dae
{
    enum class Keys
    {
        Default = 0,

        ArrowUp = 82,
        ArrowDown = 81,
        ArrowLeft = 80,
        ArrowRight = 79,

        Space = 44,
        Enter = 40,
        Escape = 41,

        A = 4,
        B = 5,
        C = 6,
        D = 7,
        E = 8,
        F = 9,
        G = 10,
        H = 11,
        I = 12,
        J = 13,
        K = 14,
        L = 15,
        M = 16,
        N = 17,
        O = 18,
        P = 19,
        Q = 20,
        R = 21,
        S = 22,
        T = 23,
        U = 24,
        V = 25,
        W = 26,
        X = 27,
        Y = 28,
        Z = 29,

        LeftCtrl = 224,
        LeftShift = 225,
        LeftAlt = 226,
        RightCtrl = 228,
        RightShift = 229,
        RightAlt = 230
    };

    class Keyboard final : public Device
    {
    public:
        Keyboard();
        virtual ~Keyboard() override;

        void ProcessInput() override;

        void ProcessActions(std::map<State, std::map<Keys, std::shared_ptr<Action>>> keyboardCommands) override;

        Keyboard(const Keyboard&) = delete;
        Keyboard(Keyboard&&) = delete;
        Keyboard& operator=(const Keyboard&) = delete;
        Keyboard& operator=(const Keyboard&&) = delete;
    private:
        bool IsPressed(Keys key) const;
        bool IsPressedThisFrame(Keys key) const;
        bool IsReleasedThisFrame(Keys key) const;

        class KeyboardImpl;
        std::unique_ptr<KeyboardImpl> m_pImpl;
    };
}