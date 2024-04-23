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
	}

	return true;
}