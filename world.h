#include <SFML/Graphics.hpp>
#include <vector>
#include "flower.h"
#include "bee.h"
#include "hornet.h"
#include "hive.h"
#ifndef P2_FOREST_15_03_24_WORLD_H
#define P2_FOREST_15_03_24_WORLD_H



class World{
public:
    std::vector< Flower* > toAddFlowers;
    std::vector< Flower* > flowers;
    std::vector< Bee* > bees;
    std::vector< Hornet* > hornets;
    std::vector<Hornet*>graduating_list;
    int stepNumber;
    std::vector< Hive* > hives;
    int width;
    int height;
    World(int width, int height);
    void draw_world(sf::RenderWindow& window);
    void make_step();
    void removeBee(Bee* bee);
    void removeHornet(Hornet* hornet);
    void check_starvation();
};

#endif //P2_FOREST_15_03_24_WORLD_H
