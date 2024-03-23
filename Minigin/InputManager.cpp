#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>

#include "InputManager.h"

dae::InputManager::InputManager() 
	: m_pDevices(static_cast<size_t>(Devices::DEVICE_COUNT))
{
	//m_pDevices[static_cast<size_t>(Devices::Keyboard)].reset(new InputKeyboard{});
	m_pDevices[static_cast<size_t>(Devices::Controller)].reset(new ControllerInput{});
}

bool dae::InputManager::ProcessInput()
{
	//for (auto& device : m_pDevices)
	//{
	//	device->ProcessInput();
	//}

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

void dae::InputManager::BindActionToKey(ControllerButton btn, KeyState keyState, std::shared_ptr<Action> pAction)
{
	m_pDevices[static_cast<size_t>(Devices::Controller)]->BindActionToKey(static_cast<unsigned>(btn), keyState, std::move(pAction));
}
