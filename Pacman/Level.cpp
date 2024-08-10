#include "Level.h"

#include <iostream>
#include <fstream>
#include "JsonFile.h"

Level::Level()
{
    // Load the level
	Load();
}

void Level::Load()
{
    // Create a JsonFile object, the file is automatically opened
    JsonFile jsonFile("level.json");

    // Access the JSON data
    const auto& levelData = jsonFile.getData();

    // Read the width and height
    int width = levelData["width"];
    int height = levelData["height"];

    // Read the grid
    std::vector<std::vector<int>> grid = levelData["grid"];

    // Print the width and height
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;

    // Print the grid
    std::cout << "Grid:" << std::endl;
    for (const auto& row : grid)
    {
        for (const auto& cell : row)
        {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}