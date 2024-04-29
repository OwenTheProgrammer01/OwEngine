#include <vector>
#include <map>
#include <iostream>

#include "Keyboard.h"
#include "Windows.h"
#include "Xinput.h"
#include "SDL.h"

class dae::Keyboard::KeyboardImpl
{
public:
	KeyboardImpl();
	~KeyboardImpl() = default;

	void ProcessInput();

	int GetKeyCode(int btn) const;
	bool IsDownThisFrame(unsigned int btn) const { return m_ButtonsPressedThisFrame & btn; }
	bool IsUpThisFrame(unsigned int btn) const { return m_ButtonsReleasedThisFrame & btn; }
	bool IsPressed(unsigned int btn) const { return m_CurrentState.Gamepad.wButtons & btn; }

private:
	XINPUT_STATE m_CurrentState;
	int m_ButtonsPressedThisFrame;
	int m_ButtonsReleasedThisFrame;
	DWORD m_KeyboardIndex;
};

dae::Keyboard::KeyboardImpl::KeyboardImpl()
	: m_CurrentState{}, m_ButtonsPressedThisFrame{}, m_ButtonsReleasedThisFrame{}, m_KeyboardIndex{}
{}

void dae::Keyboard::KeyboardImpl::ProcessInput()
{
	XINPUT_STATE previousState{};

	CopyMemory(&previousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_KeyboardIndex, &m_CurrentState);

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

	std::cout << "Pressed: " << m_ButtonsPressedThisFrame << std::endl;
}

int dae::Keyboard::KeyboardImpl::GetKeyCode(int btn) const
{
	return btn;
	//KeyboardButton button{ static_cast<KeyboardButton>(btn) };
	//
	//switch (button)
	//{
	//case KeyboardButton::A: return 0x1000;
	//case KeyboardButton::B: return 0x2000;
	//case KeyboardButton::X: return 0x4000;
	//case KeyboardButton::Y: return 0x8000;
	//
	//case KeyboardButton::DPadUp: return 0x0001;
	//case KeyboardButton::DPadDown: return 0x0002;
	//case KeyboardButton::DPadLeft: return 0x0004;
	//case KeyboardButton::DPadRight: return 0x0008;
	//
	//case KeyboardButton::LeftShoulder: return 0x0100;
	//case KeyboardButton::RightShoulder: return 0x0200;
	//
	//case KeyboardButton::Start: return 0x0010;
	//case KeyboardButton::Back: return 0x0020;
	//
	//case KeyboardButton::LeftThumb: return 0x0040;
	//case KeyboardButton::RightThumb: return 0x0080;
	//
	//default: return 0x0000;
	//}
}

dae::Keyboard::Keyboard(int userIndex)
	: Device{}, m_UserIndex(userIndex), m_pImpl(std::make_unique<KeyboardImpl>())
{}

dae::Keyboard::~Keyboard() = default;

void dae::Keyboard::ProcessInput()
{
	m_pImpl->ProcessInput();
}

int dae::Keyboard::GetKeyCode(int key) const
{
	return m_pImpl->GetKeyCode(key);
}

bool dae::Keyboard::IsDownThisFrame(int btn) const
{
	return m_pImpl->IsDownThisFrame(btn);
}

bool dae::Keyboard::IsUpThisFrame(int btn) const
{
	return m_pImpl->IsUpThisFrame(btn);
}

bool dae::Keyboard::IsPressed(int btn) const
{
	return m_pImpl->IsPressed(btn);
}