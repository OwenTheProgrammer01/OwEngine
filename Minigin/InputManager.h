#pragma once
#include <vector>
#include <map>
#include <memory>

#include "Singleton.h"
#include "Device.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		void AddDevice(std::unique_ptr<Device> pDevice);
		void RemoveDevice(int userIndex);

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
	};
}
