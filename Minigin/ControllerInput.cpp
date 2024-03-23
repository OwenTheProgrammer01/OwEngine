#include <vector>
#include <unordered_map>

#include "ControllerInput.h"
#include "Windows.h"
#include "Xinput.h"

class dae::ControllerImpl
{
public:
	ControllerImpl();
	~ControllerImpl() = default;

	void ProcessInput();
	void BindActionToKey(unsigned int key, KeyState keyState, std::shared_ptr<Action> pAction);

	unsigned int GetKeyCode(unsigned int key) const;
	bool IsDownThisFrame(unsigned int btn) const { return m_ButtonsPressedThisFrame & btn; }
	bool IsUpThisFrame(unsigned int btn) const { return m_ButtonsReleasedThisFrame & btn; }
	bool IsPressed(unsigned int btn) const { return m_CurrentState.Gamepad.wButtons & btn; }

private:
	XINPUT_STATE m_CurrentState;
	unsigned int m_ButtonsPressedThisFrame;
	unsigned int m_ButtonsReleasedThisFrame;
	std::vector<std::unordered_map<ControllerButton, std::shared_ptr<Action>>> m_ControllerKeyBinds;
};

dae::ControllerImpl::ControllerImpl()
	: m_CurrentState{}, m_ButtonsPressedThisFrame{}, m_ButtonsReleasedThisFrame{}, m_ControllerKeyBinds(static_cast<size_t>(sizeof(KeyState)))
{}

void dae::ControllerImpl::ProcessInput()
{
	DWORD userIdx{ };

	XINPUT_STATE previousState{};

	CopyMemory(&previousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(userIdx, &m_CurrentState);

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	
	for (auto& pair : m_ControllerKeyBinds[static_cast<size_t>(KeyState::UpThisFrame)]) {
		if (IsUpThisFrame(GetKeyCode(static_cast<unsigned>(pair.first))))
		{
			pair.second->Execute();
		}
	}
	for (auto& pair : m_ControllerKeyBinds[static_cast<size_t>(KeyState::DownThisFrame)]) {
		if (IsDownThisFrame(GetKeyCode(static_cast<unsigned>(pair.first))))
		{
			pair.second->Execute();
		}
	}
	for (auto& pair : m_ControllerKeyBinds[static_cast<size_t>(KeyState::Pressed)]) {
		if (IsPressed(GetKeyCode(static_cast<unsigned>(pair.first))))
		{
			pair.second->Execute();
		}
	}
}

void dae::ControllerImpl::BindActionToKey(unsigned int key, KeyState keyState, std::shared_ptr<Action> pAction)
{
	m_ControllerKeyBinds[static_cast<size_t>(keyState)][static_cast<ControllerButton>(key)] = std::move(pAction);
}

unsigned int dae::ControllerImpl::GetKeyCode(unsigned int key) const
{
	ControllerButton button{ static_cast<ControllerButton>(key) };

	switch (button)
	{
	case ControllerButton::A: return 0x1000;
	case ControllerButton::B: return 0x2000;
	case ControllerButton::X: return 0x4000;
	case ControllerButton::Y: return 0x8000;

	case ControllerButton::DPadUp: return 0x0001;
	case ControllerButton::DPadDown: return 0x0002;
	case ControllerButton::DPadLeft: return 0x0004;
	case ControllerButton::DPadRight: return 0x0008;

	case ControllerButton::LeftShoulder: return 0x0100;
	case ControllerButton::RightShoulder: return 0x0200;

	case ControllerButton::Start: return 0x0010;
	case ControllerButton::Back: return 0x0020;

	case ControllerButton::LeftThumb: return 0x0040;
	case ControllerButton::RightThumb: return 0x0080;

	default: return 0x0000;
	}
}

dae::ControllerInput::ControllerInput()
	: Device{}, m_pImpl(std::make_unique<ControllerImpl>())
{}

void dae::ControllerInput::ProcessInput()
{
	m_pImpl->ProcessInput();
}

void dae::ControllerInput::BindActionToKey(unsigned int key, KeyState keyState, std::shared_ptr<Action> pAction)
{
	m_pImpl->BindActionToKey(key, keyState, pAction);
}

unsigned int dae::ControllerInput::GetKeyCode(unsigned int key) const
{
	return m_pImpl->GetKeyCode(key);
}

bool dae::ControllerInput::IsDownThisFrame(unsigned int btn) const
{
	return m_pImpl->IsDownThisFrame(btn);
}

bool dae::ControllerInput::IsUpThisFrame(unsigned int btn) const 
{
	return m_pImpl->IsUpThisFrame(btn);
}

bool dae::ControllerInput::IsPressed(unsigned int btn) const 
{
	return m_pImpl->IsPressed(btn); 
}