#pragma once
#include "Action.h"
#include "GameActor.h"
#include "MoveComponent.h"
#include <iostream>

namespace dae
{
	class GameActorAction : public Action
	{
	protected:
		GameActor* GetGameObject() const { return m_pOwner; }
	public:
		GameActorAction(GameActor* pOwner) : m_pOwner(pOwner) {}
		virtual ~GameActorAction() = default;
	private:
		GameActor* m_pOwner;
	};

	class Movement final : public GameActorAction {
	public:
		Movement(GameActor* pOwner, const glm::vec3 direction) : GameActorAction(pOwner), m_Direction(direction) {}
		void Execute() override
		{
			std::cout << "Move" << std::endl;
			GetGameObject()->GetComponent<MoveComponent>()->Move(m_Direction);
		}
	private:
		glm::vec3 m_Direction;
	};

	class Aim final : public GameActorAction {
	public:
		Aim(GameActor* pOwner) : GameActorAction(pOwner) {}
		void Execute() override
		{
			std::cout << "Aim" << std::endl;
		}
	};

	class Shoot final : public GameActorAction {
	public:
		Shoot(GameActor* pOwner) : GameActorAction(pOwner) {}
		void Execute() override
		{
			std::cout << "Shoot" << std::endl;
		}
	};
}