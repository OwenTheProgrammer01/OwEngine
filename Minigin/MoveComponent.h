#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"
#include "GameTime.h"
#include "EventManager.h"

namespace dae
{
	class MoveComponent : public BaseComponent
	{
	public:
		MoveComponent(GameActor* pOwner) : BaseComponent(pOwner) {}
		virtual ~MoveComponent() = default;

		void Update() override {};

		void Move(const glm::vec2& speed)
		{
			auto addPosition = speed * GameTime::GetInstance().GetDeltaTime();
		}

		MoveComponent(const MoveComponent& other) = delete;
		MoveComponent(MoveComponent&& other) = delete;
		MoveComponent& operator=(const MoveComponent& other) = delete;
		MoveComponent& operator=(MoveComponent&& other) = delete;
	};
}