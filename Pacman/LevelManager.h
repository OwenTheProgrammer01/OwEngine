#pragma once
#include <string>
#include <Singleton.h>
#include <vector>
#include <memory>
#include <unordered_map>

#include "LevelBlock.h"

//TODO: Implement Collectibles
//#include "Collectible.h"

class LevelManager final : public dae::Singleton<LevelManager>
{
public:
	void LoadLevel(const std::string& levelName);

	const std::vector<glm::vec3>& GetWallPositions() const { return m_WallPositions; }

	virtual ~LevelManager() = default;
	LevelManager(const LevelManager& other) = delete;
	LevelManager(LevelManager&& other) = delete;
	LevelManager& operator=(const LevelManager& other) = delete;
	LevelManager& operator=(LevelManager&& other) = delete;
private:
	friend class dae::Singleton<LevelManager>;
	LevelManager() = default;

	const glm::vec3 m_GridStartPos{ 288, 136, 0 };
	const std::string& m_FolderPath = "../Data/LoadFiles/";
	std::vector<std::unique_ptr<LevelBlock>> m_LevelBlocks{};
	std::vector<glm::vec3> m_WallPositions;
};