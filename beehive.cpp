//
// Created by Vadim on 01.04.2024.
//

#include "beehive.h"
#include "world.h"
#include "entity.h"
#include <iostream>
Beehive::Beehive(double x, double y, double speed, World &world,sf::Color color,int needed): Hive(x, y, speed,world,color,needed){}