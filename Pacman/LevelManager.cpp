#include "LevelManager.h"
#include "JsonFile.h"
#include "Wall.h"
#include "Pellet.h"
//#include "PowerPellet.h"
#include "PlayerSpawn.h"

//TODO: change switch case (so i dont repeatedly have to write "path")

void LevelManager::LoadLevel(const std::string& levelName)
{
    // Create a JsonFile object, the file is automatically opened
    JsonFile jsonFile(m_FolderPath + levelName + ".json");

    // Access the JSON data
    const auto& levelData = jsonFile.getData();

    // Read the width and height
    int tileSize = levelData["tileSize"];
    std::vector<int> gridSize = levelData["gridSize"];

    // Read the grid
    std::vector<std::vector<int>> grid = levelData["grid"];

    // Print the grid
    int row = 0;
    for (const auto& sequence : grid) {
        int column = 0;
        for (const auto& tile : sequence) {
            auto pos = m_GridStartPos + glm::vec3(column * tileSize, row * tileSize, 0);
            switch (tile)
            {
            case 0:
                // Empty
                m_LevelBlocks.emplace_back(std::make_unique<LevelBlock>("Path", pos));
                break;
            case 1:
                // Wall
                m_LevelBlocks.emplace_back(std::make_unique<Wall>("Wall", pos));
                break;
            case 2:;
                // Path
                m_LevelBlocks.emplace_back(std::make_unique<Wall>("Path", pos));
                // Pellet
                m_LevelBlocks.emplace_back(std::make_unique<Pellet>("Pellet", pos));
                break;
            case 3:
                // Path
                m_LevelBlocks.emplace_back(std::make_unique<Wall>("Path", pos));
                // Power Pellet
                m_LevelBlocks.emplace_back(std::make_unique<Wall>("PowerPellet", pos));
                break;
            case 4:
                // Path
                m_LevelBlocks.emplace_back(std::make_unique<Wall>("Path", pos));
                break;
            case 5:
                // Path
                m_LevelBlocks.emplace_back(std::make_unique<Wall>("Path", pos));
                // Ghost Spawn Border
                //m_LevelBlocks.emplace_back(std::make_unique<Wall>("ScaredGhost", pos));
                break;
            case 6:
                // Path
                m_LevelBlocks.emplace_back(std::make_unique<Wall>("Path", pos));
                // Ghost Spawn
                m_LevelBlocks.emplace_back(std::make_unique<Wall>("Ghost1", pos));
                break;
            case 7:
                // Path
                m_LevelBlocks.emplace_back(std::make_unique<Wall>("Path", pos));
                // Player Spawn
                m_LevelBlocks.emplace_back(std::make_unique<PlayerSpawn>("Pacman", pos));
                break;
            case 8:
                // Path
                m_LevelBlocks.emplace_back(std::make_unique<Wall>("Path", pos));
                // Warp Tunnel
                //m_LevelBlocks.emplace_back(std::make_unique<Wall>("Path", pos));
                break;
            default:
                break;
            }
            column++;
        }
        row++;
    }
}