//#include <minwinbase.h>

#include "ControllerInput.h"

dae::ControllerInput::ControllerInput()
{

}

//void dae::ControllerInput::ProcessInputState()
//{
//	CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
//	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
//	XInputGetState(m_controllerIndex, &currentState);
//	auto buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
//	buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
//	buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);
//}

//void dae::ControllerInput::ProcessMappedActions()
//{
//
//}

//void dae::ControllerInput::MapActionToInput(unsigned int key, InputState inputState, std::shared_ptr<Command> pInputAction)
//{
//
//}
