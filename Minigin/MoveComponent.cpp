#include "MoveComponent.h"
#include "GameTime.h"

void dae::MoveComponent::Move(const glm::vec2& speed)
{
	auto addPosition = speed * GameTime::GetInstance().GetDeltaTime();
}