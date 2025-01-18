#include <iostream>
#include <vector>
#include <cmath>   // Pour les fonctions mathématiques (floor, pow)
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour time()
#include <string>
#include <random>
#include "generate_map.h"

// Fonction pour interpoler linéairement entre deux valeurs
float lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

// Fonction pour générer un gradient pseudo-aléatoire
float gradient(int x, int y)
{
    // Use a proper random number generator with good distribution
    static std::mt19937 gen(12345); // Seed the generator once
    static std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    // Create a unique seed for this x,y coordinate
    gen.seed(static_cast<unsigned int>(x * 49632 + y * 325176 + 12345));

    return dis(gen); // Generate value between 0 and 1
}

// Fonction pour le bruit "Perlin" 2D
float perlinNoise(float x, float y)
{
    int x0 = std::floor(x);
    int x1 = x0 + 1;
    int y0 = std::floor(y);
    int y1 = y0 + 1;

    float sx = x - x0;
    float sy = y - y0;

    float n00 = gradient(x0, y0);
    float n01 = gradient(x0, y1);
    float n10 = gradient(x1, y0);
    float n11 = gradient(x1, y1);

    float ix0 = lerp(n00, n10, sx);
    float ix1 = lerp(n01, n11, sx);

    return lerp(ix0, ix1, sy);
}

// Fonction pour générer une carte de bruit Perlin
std::vector<std::vector<float>> generatePerlinNoiseMap(int width, int height, float scale)
{
    std::vector<std::vector<float>> noiseMap(height, std::vector<float>(width));
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            float sampleX = x / scale;
            float sampleY = y / scale;
            noiseMap[y][x] = perlinNoise(sampleX, sampleY);
        }
    }
    return noiseMap;
}

// Fonction pour générer la carte principale
std::vector<std::vector<Cell>> generateMap(int width, int height, float scale, float mineralThreshold)
{
    std::srand(std::time(0)); // Initialisation aléatoire

    std::vector<std::vector<Cell>> map(height, std::vector<Cell>(width));
    std::vector<std::vector<float>> noiseMap = generatePerlinNoiseMap(width, height, scale);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            map[i][j].food_count = std::rand() % getMaxFoodPerCell(); // Nombre de pommes (0-25)
            map[i][j].minerals.resize(6, 0);         // Initialisation des minéraux

            if (noiseMap[i][j] > mineralThreshold)
            {
                for (int k = 0; k < 6; ++k)
                {
                    map[i][j].minerals[k] = std::rand() % getMaxMineralsPerCell(); // Générer des minéraux (0-25)
                }
            }
        }
    }

    return map;
}

// Fonction pour afficher la carte
void printMap(const std::vector<std::vector<Cell>> &map)
{
    const std::vector<std::string> mineralNames = {"linemate",
                                                   "deraumere",
                                                   "sibur",
                                                   "mendiane",
                                                   "phiras",
                                                   "thystame"};

    for (const auto &row : map)
    {
        for (const auto &cell : row)
        {
            std::cout << "[ ";

            if (cell.food_count > 0)
            {
                std::cout << "Food :" << cell.food_count << " ";
            }

            for (size_t k = 0; k < cell.minerals.size(); ++k)
            {
                if (cell.minerals[k] > 0)
                {
                    std::cout << mineralNames[k] << " : " << cell.minerals[k] << " ";
                }
            }

            std::cout << "] ";
        }
        std::cout << std::endl;
    }
}
