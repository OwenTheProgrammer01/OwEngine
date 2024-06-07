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

	bool IsPressed(unsigned int button) const { return m_CurrentState.Gamepad.wButtons & button; }
	bool IsPressedThisFrame(unsigned int button) const { return m_ButtonsPressedThisFrame & button; }
	bool IsReleasedThisFrame(unsigned int button) const { return m_ButtonsReleasedThisFrame & button; }
private:
	XINPUT_STATE m_CurrentState;
	int m_ButtonsPressedThisFrame;
	int m_ButtonsReleasedThisFrame;
	DWORD m_ControllerIndex;
};

dae::Controller::ControllerImpl::ControllerImpl(int controllerIndex)
	: m_CurrentState(), m_ButtonsPressedThisFrame(), m_ButtonsReleasedThisFrame(), m_ControllerIndex(static_cast<DWORD>(controllerIndex))
{}

void dae::Controller::ControllerImpl::ProcessInput()
{
	XINPUT_STATE previousState{};
	
	CopyMemory(&previousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	/*DWORD dwResult =*/ XInputGetState(m_ControllerIndex, &m_CurrentState);
	
	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	
	/* CHECK IF CONTROLLER IS CONNECTED */
	/*if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
		std::cout << "\rController is connected";
	}
	else
	{
		// Controller is not connected
		std::cout << "\rController is not connected";
	}*/
}

dae::Controller::Controller(int controllerIndex)
	: Device(), m_UserIndex(controllerIndex), m_pImpl(std::make_unique<ControllerImpl>(controllerIndex))
{}

dae::Controller::~Controller() = default;

void dae::Controller::ProcessInput()
{
	m_pImpl->ProcessInput();
}

void dae::Controller::ProcessActions(std::map<State, std::map<Buttons, std::shared_ptr<Action>>> controllerCommands)
{
	for (const auto& map : controllerCommands[State::IsPressed]) {
		if (IsPressed(static_cast<unsigned int>(map.first)))
		{
			map.second->Execute();
		}
	}
	for (const auto& map : controllerCommands[State::IsPressedThisFrame]) {
		if (IsPressedThisFrame(static_cast<unsigned int>(map.first)))
		{
			map.second->Execute();
		}
	}
	for (const auto& map : controllerCommands[State::IsReleasedThisFrame]) {
		if (IsReleasedThisFrame(static_cast<unsigned int>(map.first)))
		{
			map.second->Execute();
		}
	}
}

bool dae::Controller::IsPressed(unsigned int button) const
{
	return m_pImpl->IsPressed(button);
}

bool dae::Controller::IsPressedThisFrame(unsigned int button) const
{
	return m_pImpl->IsPressedThisFrame(button);
}

bool dae::Controller::IsReleasedThisFrame(unsigned int button) const
{
	return m_pImpl->IsReleasedThisFrame(button);
}