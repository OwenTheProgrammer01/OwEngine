//#include <vector>
//#include <map>
//
//#include "Keyboard.h"
//#include "Windows.h"
//#include "Xinput.h"
//#include "SDL.h"
//
//class dae::Keyboard::KeyboardImpl
//{
//public:
//	KeyboardImpl();
//	~KeyboardImpl() = default;
//
//	void ProcessInput();
//
//	unsigned int GetKeyCode(Keys key) const;
//	bool IsPressedThisFrame(unsigned int key) const { return m_ButtonsPressedThisFrame & key; }
//	bool IsReleasedThisFrame(unsigned int key) const { return m_ButtonsReleasedThisFrame & key; }
//	bool IsPressed(unsigned int key) const { return m_CurrentState.Gamepad.wButtons & key; }
//
//private:
//	XINPUT_STATE m_CurrentState;
//	int m_ButtonsPressedThisFrame;
//	int m_ButtonsReleasedThisFrame;
//	DWORD m_KeyboardIndex;
//};
//
//dae::Keyboard::KeyboardImpl::KeyboardImpl()
//	: m_CurrentState{}, m_ButtonsPressedThisFrame{}, m_ButtonsReleasedThisFrame{}, m_KeyboardIndex{}
//{}
//
//void dae::Keyboard::KeyboardImpl::ProcessInput()
//{
//	XINPUT_STATE previousState{};
//
//	CopyMemory(&previousState, &m_CurrentState, sizeof(XINPUT_STATE));
//	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
//	XInputGetState(m_KeyboardIndex, &m_CurrentState);
//
//	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
//	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
//	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
//}
//
//unsigned int dae::Keyboard::KeyboardImpl::GetKeyCode(Keys key) const
//{
//	switch (key)
//	{
//	case Keys::Backspace:	return static_cast<unsigned int>(VK_BACK);
//	case Keys::Tab:			return static_cast<unsigned int>(VK_TAB);
//	case Keys::Enter:		return static_cast<unsigned int>(VK_RETURN);
//	case Keys::Shift:		return static_cast<unsigned int>(VK_SHIFT);
//	case Keys::LeftShift:	return static_cast<unsigned int>(VK_LSHIFT);
//	case Keys::RightShift:	return static_cast<unsigned int>(VK_RSHIFT);
//	case Keys::Ctrl:		return static_cast<unsigned int>(VK_CONTROL);
//	case Keys::LeftCtrl:	return static_cast<unsigned int>(VK_LCONTROL);
//	case Keys::RightCtrl:	return static_cast<unsigned int>(VK_RCONTROL);
//	case Keys::Alt:			return static_cast<unsigned int>(VK_MENU);
//	case Keys::LeftAlt:		return static_cast<unsigned int>(VK_LMENU);
//	case Keys::RightAlt:	return static_cast<unsigned int>(VK_RMENU);
//	case Keys::Pause:		return static_cast<unsigned int>(VK_PAUSE);
//	case Keys::CapsLock:	return static_cast<unsigned int>(VK_CAPITAL);
//	case Keys::Escape:		return static_cast<unsigned int>(VK_ESCAPE);
//	case Keys::pageUp:		return static_cast<unsigned int>(VK_PRIOR);
//	case Keys::PageDown:	return static_cast<unsigned int>(VK_NEXT);
//	case Keys::Home:		return static_cast<unsigned int>(VK_HOME);
//	case Keys::End:			return static_cast<unsigned int>(VK_END);
//	case Keys::Left:		return static_cast<unsigned int>(VK_LEFT);
//	case Keys::Right:		return static_cast<unsigned int>(VK_RIGHT);
//	case Keys::Up:			return static_cast<unsigned int>(VK_UP);
//	case Keys::Down:		return static_cast<unsigned int>(VK_DOWN);
//	case Keys::PrintScreen:	return static_cast<unsigned int>(VK_PRINT);
//	case Keys::Insert:		return static_cast<unsigned int>(VK_INSERT);
//	case Keys::Delete:		return static_cast<unsigned int>(VK_DELETE);
//	case Keys::Key0:		return static_cast<unsigned int>(0x30);
//	case Keys::Key1:		return static_cast<unsigned int>(0x31);
//	case Keys::Key2:		return static_cast<unsigned int>(0x32);
//	case Keys::Key3:		return static_cast<unsigned int>(0x33);
//	case Keys::Key4:		return static_cast<unsigned int>(0x34);
//	case Keys::Key5:		return static_cast<unsigned int>(0x35);
//	case Keys::Key6:		return static_cast<unsigned int>(0x36);
//	case Keys::Key7:		return static_cast<unsigned int>(0x37);
//	case Keys::Key8:		return static_cast<unsigned int>(0x38);
//	case Keys::Key9:		return static_cast<unsigned int>(0x39);
//	case Keys::A:			return static_cast<unsigned int>(0x41);
//	case Keys::B:			return static_cast<unsigned int>(0x42);
//	case Keys::C:			return static_cast<unsigned int>(0x43);
//	case Keys::D:			return static_cast<unsigned int>(0x44);
//	case Keys::E:			return static_cast<unsigned int>(0x45);
//	case Keys::F:			return static_cast<unsigned int>(0x46);
//	case Keys::G:			return static_cast<unsigned int>(0x47);
//	case Keys::H:			return static_cast<unsigned int>(0x48);
//	case Keys::I:			return static_cast<unsigned int>(0x49);
//	case Keys::J:			return static_cast<unsigned int>(0x4A);
//	case Keys::K:			return static_cast<unsigned int>(0x4B);
//	case Keys::L:			return static_cast<unsigned int>(0x4C);
//	case Keys::M:			return static_cast<unsigned int>(0x4D);
//	case Keys::N:			return static_cast<unsigned int>(0x4E);
//	case Keys::O:			return static_cast<unsigned int>(0x4F);
//	case Keys::P:			return static_cast<unsigned int>(0x50);
//	case Keys::Q:			return static_cast<unsigned int>(0x51);
//	case Keys::R:			return static_cast<unsigned int>(0x52);
//	case Keys::S:			return static_cast<unsigned int>(0x53);
//	case Keys::T:			return static_cast<unsigned int>(0x54);
//	case Keys::U:			return static_cast<unsigned int>(0x55);
//	case Keys::V:			return static_cast<unsigned int>(0x56);
//	case Keys::W:			return static_cast<unsigned int>(0x57);
//	case Keys::X:			return static_cast<unsigned int>(0x58);
//	case Keys::Y:			return static_cast<unsigned int>(0x59);
//	case Keys::Z:			return static_cast<unsigned int>(0x5A);
//	case Keys::NumPad0:		return static_cast<unsigned int>(VK_NUMPAD0);
//	case Keys::NumPad1:		return static_cast<unsigned int>(VK_NUMPAD1);
//	case Keys::NumPad2:		return static_cast<unsigned int>(VK_NUMPAD2);
//	case Keys::NumPad3:		return static_cast<unsigned int>(VK_NUMPAD3);
//	case Keys::NumPad4:		return static_cast<unsigned int>(VK_NUMPAD4);
//	case Keys::NumPad5:		return static_cast<unsigned int>(VK_NUMPAD5);
//	case Keys::NumPad6:		return static_cast<unsigned int>(VK_NUMPAD6);
//	case Keys::NumPad7:		return static_cast<unsigned int>(VK_NUMPAD7);
//	case Keys::NumPad8:		return static_cast<unsigned int>(VK_NUMPAD8);
//	case Keys::NumPad9:		return static_cast<unsigned int>(VK_NUMPAD9);
//	case Keys::Multiply:	return static_cast<unsigned int>(VK_MULTIPLY);
//	case Keys::Add:			return static_cast<unsigned int>(VK_ADD);
//	case Keys::Subtract:	return static_cast<unsigned int>(VK_SUBTRACT);
//	case Keys::Decimal:		return static_cast<unsigned int>(VK_DECIMAL);
//	case Keys::Divide:		return static_cast<unsigned int>(VK_DIVIDE);
//	case Keys::F1:			return static_cast<unsigned int>(VK_F1);
//	case Keys::F2:			return static_cast<unsigned int>(VK_F2);
//	case Keys::F3:			return static_cast<unsigned int>(VK_F3);
//	case Keys::F4:			return static_cast<unsigned int>(VK_F4);
//	case Keys::F5:			return static_cast<unsigned int>(VK_F5);
//	case Keys::F6:			return static_cast<unsigned int>(VK_F6);
//	case Keys::F7:			return static_cast<unsigned int>(VK_F7);
//	case Keys::F8:			return static_cast<unsigned int>(VK_F8);
//	case Keys::F9:			return static_cast<unsigned int>(VK_F9);
//	case Keys::F10:			return static_cast<unsigned int>(VK_F10);
//	case Keys::F11:			return static_cast<unsigned int>(VK_F11);
//	case Keys::F12:			return static_cast<unsigned int>(VK_F12);
//	case Keys::NumLock:		return static_cast<unsigned int>(VK_NUMLOCK);
//	case Keys::ScrollLock:	return static_cast<unsigned int>(VK_SCROLL);
//	
//	default:				return 0x0000;
//	}
//}
//
//dae::Keyboard::Keyboard(int userIndex)
//	: Device{}, m_UserIndex(userIndex), m_pImpl(std::make_unique<KeyboardImpl>())
//{}
//
//dae::Keyboard::~Keyboard() = default;
//
//void dae::Keyboard::ProcessInput()
//{
//	m_pImpl->ProcessInput();
//}
//
//void dae::Keyboard::ProcessActions(std::map<State, std::map<Keys, std::shared_ptr<Action>>> keyboardCommands)
//{
//	for (const auto& map : keyboardCommands[State::IsPressed]) {
//		if (IsPressed(GetKeyCode(map.first)))
//		{
//			map.second->Execute();
//		}
//	}
//	for (const auto& map : keyboardCommands[State::IsPressedThisFrame]) {
//		if (IsPressedThisFrame(GetKeyCode(map.first)))
//		{
//			map.second->Execute();
//		}
//	}
//	for (const auto& map : keyboardCommands[State::IsReleasedThisFrame]) {
//		if (IsReleasedThisFrame(GetKeyCode(map.first)))
//		{
//			map.second->Execute();
//		}
//	}
//}
//
//unsigned int dae::Keyboard::GetKeyCode(Keys key) const
//{
//	return m_pImpl->GetKeyCode(key);
//}
//
//bool dae::Keyboard::IsPressed(unsigned int key) const
//{
//	return m_pImpl->IsPressed(key);
//}
//
//bool dae::Keyboard::IsPressedThisFrame(unsigned int key) const
//{
//	return m_pImpl->IsPressedThisFrame(key);
//}
//
//bool dae::Keyboard::IsReleasedThisFrame(unsigned int key) const
//{
//	return m_pImpl->IsReleasedThisFrame(key);
//}