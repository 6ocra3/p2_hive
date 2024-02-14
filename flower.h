//
// Created by Макар Кряжев on 10.02.2024.
//
#include <SFML/Graphics.hpp>
#include "entity.h"
class World;
class Bee;
#ifndef P2_FOREST_15_03_24_FLOWERS_H
#define P2_FOREST_15_03_24_FLOWERS_H
class Flower : public Entity{
public:
    Bee* bee;
    int capacity;
    int greenCnt;
    bool busy;
    Flower(double x, double y, double speed, World& world);
    void make_step() override;
};
#endif //P2_FOREST_15_03_24_FLOWERS_H
