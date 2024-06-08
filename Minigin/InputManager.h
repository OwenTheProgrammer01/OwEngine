#pragma once
#include <vector>
#include <map>
#include <memory>

#include "Singleton.h"
#include "Controller.h"
#include "Keyboard.h"
#include "GameActorAction.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		void AddDevice(std::unique_ptr<Device> pDevice);
		void RemoveDevice(int userIndex);

		void BindCommand(State state, Keys key, std::shared_ptr<Action> command); // For keyboard input
		void BindCommand(State state, Buttons button, std::shared_ptr<Action> command); // For controller input

		bool ProcessInput();

		virtual ~InputManager() = default;
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;
	private:
		friend class Singleton<InputManager>;
		InputManager() = default;

		std::vector<std::unique_ptr<Device>> m_pDevices;

		std::map<State, std::map<Keys, std::shared_ptr<Action>>> m_keyboardCommands; // state -> key -> action
		std::map<State, std::map<Buttons, std::shared_ptr<Action>>> m_controllerCommands; // state -> button -> action
	};
}
