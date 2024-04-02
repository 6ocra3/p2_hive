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
public:
    void spawn() override{
        Hornet hornet = Hornet(this->x, this->y, 8, world,*this);
        world.hornets.push_back(hornet);
    }
    Hornethive(double x, double y, double speed, World& world,sf::Color color,int needed);
};
#endif //P2_FOREST_15_03_24_HORNETHIVE_H
