#pragma once
#include "LevelBlock.h"

class Pellet final : public LevelBlock
{
public:
	Pellet(const std::string& type, const glm::vec3& worldPos) : LevelBlock(type, worldPos) {}
	~Pellet() override = default;

	Pellet(const Pellet& other) = delete;
	Pellet(Pellet&& other) = delete;
	Pellet& operator=(const Pellet& other) = delete;
	Pellet& operator=(Pellet&& other) = delete;
};