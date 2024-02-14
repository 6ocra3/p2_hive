#include "bee.h"
#include "hornet.h"
#include "world.h"
#include "utils.cpp"
#include "entity.h"
Hornet::Hornet(double x, double y, double speed, World& world): Entity(x, y, speed, world, sf::Color::Red), goal(nullptr){

}

void Hornet::make_step() {
    double curdist = 1000000;
    for(Bee& bee : world.bees){
        double newDist = get_distance(*this, bee);
        if(newDist < curdist){
            curdist = newDist;
            goal = &bee;
        }
    }

    double dx = goal->x - this->x;
    double dy = goal->y - this->y;

    double length = sqrt(dx * dx + dy * dy);
    double dx_normalized = dx / length;
    double dy_normalized = dy / length;



    double stepX = dx_normalized * this->speed;
    double stepY = dy_normalized * this->speed;

    this->x += stepX;
    this->y += stepY;

    this->shape.move(stepX, stepY);

}
