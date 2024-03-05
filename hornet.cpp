#include "bee.h"
#include "hornet.h"
#include "world.h"
#include "utils.cpp"
#include "entity.h"
#include "iostream"
Hornet::Hornet(double x, double y, double speed, World& world): Entity(x, y, speed, world, sf::Color::Red), goal(nullptr), stepAttacks(0){

}

void Hornet::find_goal(){
    double curdist = 1000000;
    for(Bee* bee : world.bees){
        double newDist = get_distance(*this, *bee);
        if(newDist < curdist){
            curdist = newDist;
            goal = bee;
        }
    }
}

void Hornet::make_step() {

    this->find_goal();

    if(get_distance(*this, *goal) < 15){
        stepAttacks++;
    }
    else{
        stepAttacks = 0;
    }
    if(stepAttacks == 10){
        world.removeBee(goal);
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
