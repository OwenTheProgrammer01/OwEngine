#pragma once
#include "Action.h"
#include "GameObject.h"
#include <iostream>

namespace dae
{
	class GameObjectAction : public Action
	{
	protected:
		GameObject* GetGameObject() const { return m_pOwner; }
	public:
		GameObjectAction(GameObject* pOwner) : m_pOwner(pOwner) {}
		virtual ~GameObjectAction() = default;
	private:
		GameObject* m_pOwner;
	};

	class Movement final : public GameObjectAction {
	public:
		Movement(GameObject* pOwner) : GameObjectAction(pOwner) {}
		void Execute() override
		{
			std::cout << "Move" << std::endl;
			//GetGameObject()->GetComponent<>();
		}
	};

	class Aim final : public GameObjectAction {
	public:
		Aim(GameObject* pOwner) : GameObjectAction(pOwner) {}
		void Execute() override
		{
			std::cout << "Aim" << std::endl;
		}
	};

	class Shoot final : public GameObjectAction {
	public:
		Shoot(GameObject* pOwner) : GameObjectAction(pOwner) {}
		void Execute() override
		{
			std::cout << "Shoot" << std::endl;
		}
	};
}