#pragma once
#include <vector>
#include <map>

#include "Singleton.h"
#include "GameObjectAction.h"
#include "ControllerInput.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		void BindAction(int key, int keyState, Action* pAction);
		void BindAction(int button, Action* pAction);

		~InputManager() = default;
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;
	private:
		friend class Singleton<InputManager>;
		InputManager() {};

		std::map<int, std::map<int, Action*>> keyboardActions;
		std::map<int, Action*> controllerActions;
	};
}
