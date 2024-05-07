#pragma once
#include <vector>
#include <map>
#include <memory>

#include "Singleton.h"
#include "Controller.h"
#include "Keyboard.h"
#include "GameObjectAction.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		void AddDevice(std::unique_ptr<Device> pDevice);
		void RemoveDevice(int userIndex);

		//void BindCommand(int key, int keystate, Action* command); // For keyboard input
		void BindCommand(ControllerButton button, std::shared_ptr<Action> command); // For controller input

		bool ProcessInput();

		InputManager() = default;
		~InputManager() = default;
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;
	private:
		friend class Singleton<InputManager>;

		std::vector<std::unique_ptr<Device>> m_pDevices;

		std::map<int, std::map<int, Action*>> keyboardCommands; // key -> keystate -> action
		std::map<ControllerButton, std::shared_ptr<Action>> controllerCommands; // button -> action
	};
}
