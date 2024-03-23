#pragma once
#include <vector>

#include "Singleton.h"
#include "GameObjectAction.h"
#include "ControllerInput.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		void BindActionToKey(ControllerButton button, KeyState keyState, std::shared_ptr<Action> pAction);

		~InputManager() = default;
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;
	private:
		friend class Singleton<InputManager>;
		InputManager();

		std::vector<std::unique_ptr<Device>> m_pDevices;

		enum class Devices : char
		{
			Keyboard,
			//Mouse,
			Controller,

			DEVICE_COUNT
		};
	};
}
