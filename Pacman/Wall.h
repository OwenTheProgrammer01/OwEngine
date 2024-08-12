#pragma once
#include <glm/glm.hpp>
#include "LevelBlock.h"

class Wall final : public LevelBlock
{
public:
	Wall(const std::string& type, const glm::vec3& worldPos) : LevelBlock(type, worldPos) {}
	~Wall() override = default;

	Wall(const Wall&) = delete;
	Wall(Wall&&) = delete;
	Wall& operator=(const Wall&) = delete;
	Wall& operator=(Wall&&) = delete;
};