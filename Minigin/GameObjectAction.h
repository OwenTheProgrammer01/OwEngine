#pragma once
#include "Action.h"
#include "GameActor.h"
#include <iostream>

namespace dae
{
	class GameObjectAction : public Action
	{
	protected:
		GameActor* GetGameObject() const { return m_pOwner; }
	public:
		GameObjectAction(GameActor* pOwner) : m_pOwner(pOwner) {}
		virtual ~GameObjectAction() = default;
	private:
		GameActor* m_pOwner;
	};

	class Movement final : public GameObjectAction {
	public:
		Movement(GameActor* pOwner) : GameObjectAction(pOwner) {}
		void Execute() override
		{
			std::cout << "Move" << std::endl;
			//GetGameObject()->GetComponent<>();
		}
	};

	class Aim final : public GameObjectAction {
	public:
		Aim(GameActor* pOwner) : GameObjectAction(pOwner) {}
		void Execute() override
		{
			std::cout << "Aim" << std::endl;
		}
	};

	class Shoot final : public GameObjectAction {
	public:
		Shoot(GameActor* pOwner) : GameObjectAction(pOwner) {}
		void Execute() override
		{
			std::cout << "Shoot" << std::endl;
		}
	};
}