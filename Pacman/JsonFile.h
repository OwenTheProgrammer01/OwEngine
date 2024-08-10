#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

class JsonFile 
{
public:
    // Constructor opens the file
    JsonFile(const std::string& filePath) {
        file.open(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open the file: " + filePath);
        }
        file >> jsonData;
    }

    // Destructor closes the file
    ~JsonFile()
    {
        if (file.is_open()) { file.close(); }
    }

    // Function to get the JSON data
    const json& getData() const { return jsonData; }

    JsonFile(const JsonFile&) = delete;
    JsonFile(JsonFile&& other) = delete;
    JsonFile& operator=(const JsonFile&) = delete;
    JsonFile& operator=(JsonFile&& other) = delete;
private:
    std::ifstream file;
    json jsonData;
};