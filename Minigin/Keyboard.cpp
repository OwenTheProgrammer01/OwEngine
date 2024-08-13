#include "Keyboard.h"
#include <SDL.h>

class dae::Keyboard::KeyboardImpl
{
public:
	KeyboardImpl();
	~KeyboardImpl() = default;

	void ProcessInput();

	bool IsPressed(Keys key) const { return m_CurrentKeyState[static_cast<int>(key)]; }
	bool IsPressedThisFrame(Keys key) const { return m_CurrentKeyState[static_cast<int>(key)] && !m_PreviousKeyState[static_cast<int>(key)]; }
	bool IsReleasedThisFrame(Keys key) const { return !m_CurrentKeyState[static_cast<int>(key)] && m_PreviousKeyState[static_cast<int>(key)]; }
private:
    const Uint8* m_CurrentKeyState;
    Uint8 m_PreviousKeyState[SDL_NUM_SCANCODES];
    int m_NumKeys;
};

dae::Keyboard::KeyboardImpl::KeyboardImpl()
	: m_CurrentKeyState(nullptr), m_PreviousKeyState(), m_NumKeys(0)
{
    m_CurrentKeyState = SDL_GetKeyboardState(&m_NumKeys);
    std::copy(m_CurrentKeyState, m_CurrentKeyState + m_NumKeys, m_PreviousKeyState);
}

void dae::Keyboard::KeyboardImpl::ProcessInput()
{
    // Update the previous state before processing the new state
    std::copy(m_CurrentKeyState, m_CurrentKeyState + m_NumKeys, m_PreviousKeyState);
    SDL_PumpEvents(); // Update the current key state
}

dae::Keyboard::Keyboard()
    : Device(), m_pImpl(std::make_unique<KeyboardImpl>())
{}

dae::Keyboard::~Keyboard() = default;

void dae::Keyboard::ProcessInput()
{
    m_pImpl->ProcessInput();
}

void dae::Keyboard::ProcessActions(std::map<State, std::map<Keys, std::shared_ptr<Action>>> keyboardCommands)
{
    for (const auto& map : keyboardCommands[State::IsPressed]) {
        if (IsPressed(map.first))
        {
            map.second->Execute();
        }
    }
    for (const auto& map : keyboardCommands[State::IsPressedThisFrame]) {
        if (IsPressedThisFrame(map.first))
        {
            map.second->Execute();
        }
    }
    for (const auto& map : keyboardCommands[State::IsReleasedThisFrame]) {
        if (IsReleasedThisFrame(map.first))
        {
            map.second->Execute();
        }
    }
}

bool dae::Keyboard::IsPressed(Keys key) const
{
    return m_pImpl->IsPressed(key);
}

bool dae::Keyboard::IsPressedThisFrame(Keys key) const
{
    return m_pImpl->IsPressedThisFrame(key);

}

bool dae::Keyboard::IsReleasedThisFrame(Keys key) const
{
    return m_pImpl->IsReleasedThisFrame(key);
}