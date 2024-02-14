#include <SFML/Graphics.hpp>
#include <vector>
#include "flower.h"
#include "bee.h"
#include "hornet.h"
#ifndef P2_FOREST_15_03_24_WORLD_H
#define P2_FOREST_15_03_24_WORLD_H



class World{
public:
    std::vector< Flower > toAddFlowers;
    std::vector< Flower > flowers;
    std::vector< Bee > bees;
    std::vector< Hornet > hornets;
    int stepNumber;
    World();
    void draw_world(sf::RenderWindow& window);
    void make_step();
};

#endif //P2_FOREST_15_03_24_WORLD_H
