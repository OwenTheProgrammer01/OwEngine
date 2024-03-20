#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>
//#include <minwinbase.h>

#include "InputManager.h"
//#include "XInput.h"
//#include "Windows.h"

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
		// etc...

		//process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	//CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
	//ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	//XInputGetState(m_controllerIndex, &currentState);
	//auto buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
	//buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
	//buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);

	return true;
}
