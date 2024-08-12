#pragma once
#include <glm/glm.hpp>
#include <string>

class LevelBlock
{
public:
	explicit LevelBlock(const std::string& type, const glm::vec3& worldPos);
	virtual ~LevelBlock() = default;

	LevelBlock(const LevelBlock&) = delete;
	LevelBlock(LevelBlock&&) = delete;
	LevelBlock& operator=(const LevelBlock&) = delete;
	LevelBlock& operator=(LevelBlock&&) = delete;
};