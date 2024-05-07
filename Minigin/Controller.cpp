#include <vector>
#include <map>
#include <iostream>

#include "Controller.h"
#include "Windows.h"
#include "Xinput.h"

class dae::Controller::ControllerImpl
{
public:
	ControllerImpl(int controllerIndex);
	~ControllerImpl() = default;

	void ProcessInput();

	int GetKeyCode(int btn) const;
	bool IsDownThisFrame(unsigned int btn) const { return m_ButtonsPressedThisFrame & btn; }
	bool IsUpThisFrame(unsigned int btn) const { return m_ButtonsReleasedThisFrame & btn; }
	bool IsPressed(unsigned int btn) const { return m_CurrentState.Gamepad.wButtons & btn; }

private:
	XINPUT_STATE m_CurrentState;
	int m_ButtonsPressedThisFrame;
	int m_ButtonsReleasedThisFrame;
	DWORD m_ControllerIndex;
};

dae::Controller::ControllerImpl::ControllerImpl(int controllerIndex)
	: m_CurrentState{}, m_ButtonsPressedThisFrame{}, m_ButtonsReleasedThisFrame{}, m_ControllerIndex{ static_cast<DWORD>(controllerIndex) }
{}

void dae::Controller::ControllerImpl::ProcessInput()
{
	XINPUT_STATE previousState{};
	
	CopyMemory(&previousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(m_ControllerIndex, &m_CurrentState);
	
	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	
	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
		std::cout << "\rController is connected";
	}
	else
	{
		// Controller is not connected
		std::cout << "\rController is not connected";
	}
}

int dae::Controller::ControllerImpl::GetKeyCode(int btn) const
{
	ControllerButton button{ static_cast<ControllerButton>(btn) };

	switch (button)
	{
	case ControllerButton::DPadUp: return 0x0001;
	case ControllerButton::DPadDown: return 0x0002;
	case ControllerButton::DPadLeft: return 0x0004;
	case ControllerButton::DPadRight: return 0x0008;

	case ControllerButton::Start: return 0x0010;
	case ControllerButton::Back: return 0x0020;

	case ControllerButton::LeftThumb: return 0x0040;
	case ControllerButton::RightThumb: return 0x0080;

	case ControllerButton::LeftShoulder: return 0x0100;
	case ControllerButton::RightShoulder: return 0x0200;

	case ControllerButton::A: return 0x1000;
	case ControllerButton::B: return 0x2000;
	case ControllerButton::X: return 0x4000;
	case ControllerButton::Y: return 0x8000;

	default: return 0x0000;
	}
}

dae::Controller::Controller(int controllerIndex)
	: Device{}, m_UserIndex(controllerIndex), m_pImpl(std::make_unique<ControllerImpl>(controllerIndex))
{}

dae::Controller::~Controller() = default;

void dae::Controller::ProcessInput()
{
	m_pImpl->ProcessInput();
}

int dae::Controller::GetKeyCode(int key) const
{
	return m_pImpl->GetKeyCode(key);
}

bool dae::Controller::IsDownThisFrame(int btn) const
{
	return m_pImpl->IsDownThisFrame(btn);
}

bool dae::Controller::IsUpThisFrame(int btn) const 
{
	return m_pImpl->IsUpThisFrame(btn);
}

bool dae::Controller::IsPressed(int btn) const 
{
	return m_pImpl->IsPressed(btn); 
}