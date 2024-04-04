#include "bee.h"
#include "hornet.h"
#include "world.h"
#include "utils.cpp"
#include "entity.h"
#include "iostream"
Hornet::Hornet(double x, double y, double speed, World& world,Hive& hive): Entity(x, y, speed, world, sf::Color::Red), goal(nullptr), stepAttacks(0)
,inhive(false),taken(0),hive(&hive){

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

//void Hornet::go_to(Entity &first) {
//    double dx = first.x - this->x;
//    double dy = first.y - this->y;
//
//    double length = sqrt(dx * dx + dy * dy);
//    double dx_normalized = dx / length;
//    double dy_normalized = dy / length;
//
//    double stepX = dx_normalized * this->speed;
//    double stepY = dy_normalized * this->speed;
//
//    this->x += stepX;
//    this->y += stepY;
//
//    this->shape.move(stepX, stepY);
//}

void Hornet::make_step() {
    if(this->starve < 80){
        if((this->taken>=10)or(this->inhive)){
            if(inhive){
                if (world.stepNumber % 2 == 0) {
                    if (this->taken > 0) {
                        taken -= 1;
                        hive->addResources(1);
                    }
                    if (taken == 0) {
                        this->find_goal();
                        this->inhive = false;
                        shape.setRadius(10.f);
                        shape.setFillColor(sf::Color::Red);
                        shape.setOutlineThickness(0);
                        this->starve = 0;
                    }
                }
            }
            else{
                if(get_distance(*this,*hive)<=speed){
                    inhive = true;
                    shape.setRadius(10.f);
                    shape.setFillColor(sf::Color::Red);
                    shape.setOutlineThickness(0);
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
                this->starve=0;
            }
            this->go_to(*goal);
            this->starve+=2;
        }
    }
    else{
        world.removeHornet(this);
    }
}

Hornet::~Hornet(){
    auto it = std::find(world.hornets.begin(), world.hornets.end(), this);
    if (it != world.hornets.end()) {
        world.hornets.erase(it);
    }

    for(Bee* bee : world.bees){
        if(bee->compare_closets(this)){
            bee->change_closest(nullptr);
        }
    }

}