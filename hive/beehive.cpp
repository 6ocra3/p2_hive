//
// Created by Vadim on 01.04.2024.
//

#include "beehive.h"
#include "../others/world.h"
#include "../entity/entity.h"
#include "../others/utils.cpp"
#include "../others/globals.h"
Beehive::Beehive(double x, double y, double speed, World &world,sf::Color color,int needed): Hive(x, y, speed,world,color,needed){}
void Beehive::spawn() {
    speed = randint(1,15)/10+5;
    Bee* bee = new Bee(getX(), getY(), speed, world, *this);
    world.bees.push_back(bee);
}