#include "MoveComponent.h"
#include "GameTime.h"
#include <iostream>

void dae::MoveComponent::Move(const glm::vec2& dir)
{
	GetOwner()->SetWorldPosition(GetOwner()->GetWorldPosition() + glm::vec3((dir * GameTime::GetInstance().GetDeltaTime() * m_Speed), 0));
}