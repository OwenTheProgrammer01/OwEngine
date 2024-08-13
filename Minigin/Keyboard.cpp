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
    Uint8 m_CurrentKeyState[SDL_NUM_SCANCODES];
    Uint8 m_PreviousKeyState[SDL_NUM_SCANCODES];
};

dae::Keyboard::KeyboardImpl::KeyboardImpl()
    : m_CurrentKeyState(), m_PreviousKeyState()
{
    // Initialize arrays
    std::fill(std::begin(m_CurrentKeyState), std::end(m_CurrentKeyState), static_cast<Uint8>(0));
    std::fill(std::begin(m_PreviousKeyState), std::end(m_PreviousKeyState), static_cast<Uint8>(0));
}

void dae::Keyboard::KeyboardImpl::ProcessInput()
{
    // Update the previous state before processing the new state
    std::copy(std::begin(m_CurrentKeyState), std::end(m_CurrentKeyState), std::begin(m_PreviousKeyState));
    
    // Pump SDL events to update the keyboard state
    SDL_PumpEvents(); // Update the internal state of SDL
    
    // Get the current state of the keyboard
    const Uint8* currentKeyState = SDL_GetKeyboardState(nullptr);
    
    // Copy the new state into m_CurrentKeyState
    std::copy(currentKeyState, currentKeyState + SDL_NUM_SCANCODES, std::begin(m_CurrentKeyState));
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