#ifndef ZAPPY_SERVER_GENERATE_MAP_H
#define ZAPPY_SERVER_GENERATE_MAP_H

// ... existing 
#include <vector>
#include <string>

// Mineral structure definition
struct mineral {
    enum type {
        linemate,
        deraumere,
        sibur,
        mendiane,
        phiras,
        thystame
    };
    uint32_t quantity = 0;
};

// Cell structure definition
struct Cell {
    int food_count;            // Number of food items in the cell
    std::vector<int> minerals; // Quantity of each mineral type (0-4 types)
};

// Constants
constexpr static int getMaxFoodPerCell() { return 26; }
constexpr static int getMaxMineralsPerCell() { return 26; }

// Function prototypes
float lerp(float a, float b, float t);
float gradient(int x, int y);
float perlinNoise(float x, float y);
std::vector<std::vector<float>> generatePerlinNoiseMap(int width, int height, float scale);
std::vector<std::vector<Cell>> generateMap(int width, int height, float scale, float mineralThreshold);
void printMap(const std::vector<std::vector<Cell>>& map); 

#endif // ZAPPY_SERVER_GENERATE_MAP_H
