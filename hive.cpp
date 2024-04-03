//
// Created by Vadim on 22.02.2024.
//
#include "world.h"
#include "entity.h"
#include <iostream>
Hive::Hive(double x, double y, double speed, World& world,sf::Color color,int needed): Entity(x, y, speed, world, color),needed(needed){}
void Hive::make_step(){
    std::cout<< "honey: "<<this->resourses<<"\n";
    if((resourses>=needed)and(world.stepNumber % 50 == 0)){
        while(resourses>=needed){
            resourses-=needed;
            spawn();
        }
    }
}