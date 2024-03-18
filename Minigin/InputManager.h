#pragma once
#include "Singleton.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		//InputManager(const InputManager& other) = delete;
		//InputManager(InputManager&& other) = delete;
		//InputManager& operator=(const InputManager& other) = delete;
		//InputManager& operator=(InputManager&& other) = delete;
	};
}
