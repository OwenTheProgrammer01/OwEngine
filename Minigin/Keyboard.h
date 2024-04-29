#pragma once
#include "Device.h"

namespace dae
{
    class Keyboard final : public Device
    {
    public:
        Keyboard(int userIndex);
        virtual ~Keyboard() override;

        void ProcessInput() override;

        Keyboard(const Keyboard&) = delete;
        Keyboard(Keyboard&&) = delete;
        Keyboard& operator=(const Keyboard&) = delete;
        Keyboard& operator=(const Keyboard&&) = delete;

    private:
        int m_UserIndex;

        class KeyboardImpl;
        std::unique_ptr<KeyboardImpl> m_pImpl;

        int GetKeyCode(int key) const;
        bool IsDownThisFrame(int btn) const;
        bool IsUpThisFrame(int btn) const;
        bool IsPressed(int btn) const;
    };
}