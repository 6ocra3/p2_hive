//
// Created by Vadim on 22.02.2024.
//
#include "world.h"
#include "entity.h"
#include <iostream>
Hive::Hive(double x, double y, double speed, World& world): Entity(x, y, speed, world, sf::Color::Cyan){}
void Hive::make_step() {
    std::cout<< "honey: "<<this->honey<<"\n";
    if((honey>=10)and(world.stepNumber % 50 == 0)){
        while(honey>=10){
            honey-=10;
            long sp = 6;
            Bee* bee = new Bee(x, y, sp, world);
            world.bees.push_back(bee);
        }
    }
}