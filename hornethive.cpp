//
// Created by Vadim on 02.04.2024.
//
#include "hornethive.h"
#include "world.h"
#include "entity.h"
#include "utils.cpp"
Hornethive::Hornethive(double x, double y, double speed, World &world,sf::Color color,int needed): Hive(x, y, speed,world,color,needed){}
void Hornethive::spawn() {
    speed = randint(1,15)/10+6;
    Hornet* hornet = new Hornet(this->x, this->y, speed, world, *this);
    world.hornets.push_back(hornet);
}