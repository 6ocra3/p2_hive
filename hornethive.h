//
// Created by Vadim on 01.04.2024.
//
#ifndef P2_FOREST_15_03_24_HORNETHIVE_H
#define P2_FOREST_15_03_24_HORNETHIVE_H
#include "world.h"
#include "entity.h"
#include <iostream>
#include "hive.h"
#include "hornet.h"
class Hornethive: public Hive{
private:
    void spawn() override;
public:
    Hornethive(double x, double y, double speed, World& world,sf::Color color,int needed);
};
#endif //P2_FOREST_15_03_24_HORNETHIVE_H
