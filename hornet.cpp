#include "bee.h"
#include "hornet.h"
#include "world.h"
#include "utils.cpp"
#include "entity.h"
#include "iostream"
Hornet::Hornet(double x, double y, double speed, World& world): Entity(x, y, speed, world, sf::Color::Red), goal(nullptr), stepAttacks(0)
,inhive(false),hive(world.hives[1]),taken(0){

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

void Hornet::go_to(Entity &first) {
    double dx = first.x - this->x;
    double dy = first.y - this->y;

    double length = sqrt(dx * dx + dy * dy);
    double dx_normalized = dx / length;
    double dy_normalized = dy / length;

    double stepX = dx_normalized * this->speed;
    double stepY = dy_normalized * this->speed;

    this->x += stepX;
    this->y += stepY;

    this->shape.move(stepX, stepY);
}

void Hornet::make_step() {
    if((this->taken>=10)or(this->inhive)){
        if(inhive){
            if (world.stepNumber % 5 == 0) {
                if (this->taken > 0) {
                    taken -= 1;
                    hive->resourses += 1;
                    return;
                }
                if (taken == 0) {
                    this->find_goal();
                    this->inhive = false;
                    shape.setRadius(10.f);
                    shape.setFillColor(sf::Color::Yellow);
                    shape.setOutlineThickness(0);
                    return;
                }
            }
        }
        else{
            if(get_distance(*this,*hive)<=speed){
                inhive = true;
            }
            else{
                this->go_to(*hive);
            }
        }
    }
    else{
        this->find_goal();

        if(get_distance(*this, *goal) < 15){
            stepAttacks++;
        }
        else{
            stepAttacks = 0;
        }
        if(stepAttacks == 10){
            this->taken+=10;
            world.removeBee(goal);
        }

        this->go_to(*goal);
    }
}
