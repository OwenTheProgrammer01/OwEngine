#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"
#include "GameTime.h"
#include "EventManager.h"
#include "GameActor.h"
#include "Transform.h"

namespace dae
{
	class MoveComponent final : public BaseComponent
	{
	public:
		MoveComponent(GameActor* pOwner) : BaseComponent(pOwner) {}
		virtual ~MoveComponent() = default;

		void Update() override {}

		void Move(const glm::vec2& dir);

		MoveComponent(const MoveComponent& other) = delete;
		MoveComponent(MoveComponent&& other) = delete;
		MoveComponent& operator=(const MoveComponent& other) = delete;
		MoveComponent& operator=(MoveComponent&& other) = delete;
	private:
		glm::vec2 m_Speed{ 100, 100 };
	};
}