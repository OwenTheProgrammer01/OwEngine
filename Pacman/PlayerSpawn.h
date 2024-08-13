#pragma once
#include "LevelBlock.h"

class PlayerSpawn final : public LevelBlock
{
public:
	PlayerSpawn(const std::string& character, const glm::vec3& worldPos);
	~PlayerSpawn() override = default;

	PlayerSpawn(const PlayerSpawn&) = delete;
	PlayerSpawn(PlayerSpawn&&) = delete;
	PlayerSpawn& operator=(const PlayerSpawn&) = delete;
	PlayerSpawn& operator=(PlayerSpawn&&) = delete;
};