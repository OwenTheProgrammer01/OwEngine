#pragma once
#include "BaseComponent.h"
#include <string>
#include <glm/glm.hpp>
#include <vector>

class GameActor;
class PlayerComponent final : public dae::BaseComponent
{
public:
	void Update() override;
	void Render() const override;

	bool IsCollidingWithWall(const glm::vec3& newPos, const std::vector<glm::vec3>& wallPositions);

	PlayerComponent(dae::GameActor* pOwner);
	virtual ~PlayerComponent() = default;

	PlayerComponent(const PlayerComponent& other) = delete;
	PlayerComponent(PlayerComponent&& other) = delete;
	PlayerComponent& operator=(const PlayerComponent& other) = delete;
	PlayerComponent& operator=(PlayerComponent&& other) = delete;
private:
	const glm::vec3 m_Speed;
};