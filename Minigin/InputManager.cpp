#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>

#include "InputManager.h"

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
	return true;
}

void dae::InputManager::BindAction(int key, int keystate, Action* pAction) 
{
	keyboardActions[key][keystate] = pAction;
}

void dae::InputManager::BindAction(int button, Action* pAction) 
{
	controllerActions[button] = pAction;
}
