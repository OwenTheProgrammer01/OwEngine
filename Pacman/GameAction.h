#pragma once
#include "GameActorAction.h"

class PacmanMovement final : public dae::GameActorAction {
public:
	PacmanMovement(dae::GameActor* pOwner, const glm::vec3 direction) : dae::GameActorAction(pOwner), m_Direction(direction)
	{
		m_Direction = glm::normalize(glm::vec3{ direction.x, -direction.y, 0 });
	}
	void Execute() override
	{
		GetGameObject()->Translate(m_Direction);
	}
private:
	glm::vec3 m_Direction;
};