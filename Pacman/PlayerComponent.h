#pragma once
#include "BaseComponent.h"
#include <string>
#include <glm/glm.hpp>

class GameActor;
class PlayerComponent final : public dae::BaseComponent
{
public:
	void Update() override;
	void Render() const override;

	PlayerComponent(dae::GameActor* pOwner);
	virtual ~PlayerComponent() = default;

	PlayerComponent(const PlayerComponent& other) = delete;
	PlayerComponent(PlayerComponent&& other) = delete;
	PlayerComponent& operator=(const PlayerComponent& other) = delete;
	PlayerComponent& operator=(PlayerComponent&& other) = delete;
};