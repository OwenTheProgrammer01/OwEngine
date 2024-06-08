#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>

#include "InputManager.h"

void dae::InputManager::AddDevice(std::unique_ptr<Device> pDevice)
{
	m_pDevices.emplace_back(std::move(pDevice));
}

void dae::InputManager::RemoveDevice(int userIndex)
{
	if (userIndex >= 0 && userIndex < m_pDevices.size())
	{
		m_pDevices.erase(m_pDevices.begin() + userIndex);
	}
}

//void dae::InputManager::BindCommand(State state, Keys key, std::shared_ptr<Action> action)
//{
//	m_keyboardCommands[state][key] = action;
//}

void dae::InputManager::BindCommand(State state, Buttons button, std::shared_ptr<Action> action)
{
	m_controllerCommands[state][button] = action;
}

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

	for (const auto& device : m_pDevices) {
		device->ProcessInput();
		device->ProcessActions(m_controllerCommands);
		//device->ProcessActions(m_keyboardCommands);
	}

	return true;
}