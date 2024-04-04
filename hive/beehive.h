//
// Created by Vadim on 01.04.2024.
//
#include <algorithm>
#ifndef P2_FOREST_15_03_24_BEEHIVE_H
#define P2_FOREST_15_03_24_BEEHIVE_H

#include "../others/world.h"
#include "../entity/entity.h"
#include <iostream>
#include "hive.h"
class Beehive: public Hive{
public:
    Beehive(double x, double y, double speed, World& world,sf::Color color,int needed);
private:
    void spawn() override;
};



#endif //P2_FOREST_15_03_24_BEEHIVE_H
