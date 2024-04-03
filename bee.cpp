#include "bee.h"
#include "flower.h"
#include "world.h"
#include "utils.cpp"
#include "entity.h"
#include <iostream>
#include "vector"
#include "beehive.h"
Bee::Bee(double x, double y, double speed, World& world,Hive& hive): Entity(x, y, speed, world, sf::Color::Yellow), goal(nullptr), taken(0), inGoal(
        false),inHive(false),hive(&hive){}
void Bee::find_goal(){
    if(this->goal != nullptr){
        this->goal->bee = nullptr;
        this->goal = nullptr;
    }
    std::vector < std::pair< double, Flower*  > > closestFlowers;
    for(Flower* flower : world.flowers){
        if(flower->capacity > 0){
            std::pair< double, Flower* > newPair;
            newPair.first = get_distance(*this, *flower);
            newPair.second = flower;
            closestFlowers.push_back(newPair);
        }
    }
    std::sort( closestFlowers.begin(), closestFlowers.end() );
    for(std::pair< double, Flower* > closestFlower: closestFlowers){
        if(closestFlower.second->bee == nullptr || closestFlower.second->bee == this){
            goal = closestFlower.second;
            closestFlower.second->bee = this;
            return;
        }
        else if(get_distance(*closestFlower.second->bee, *closestFlower.second) > get_distance(*this, *closestFlower.second)){
            this->goal = closestFlower.second;
            Bee* prevBee = closestFlower.second->bee;
            this->goal->bee = this;
            prevBee->goal = nullptr;
            prevBee->find_goal();
            return;
        }
    }
}
void Bee::go_to(Entity& first){
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

bool Bee::set_status(Entity& first) {
    this->x = first.x;
    this->y = first.y;
    shape.setPosition(this->x, this->y);
    shape.setRadius(10.f);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(2.5f);
    shape.setOutlineColor(sf::Color::Yellow);
    return true;
}

void Bee::harvest() {
    if(goal->capacity > 0){
        this->taken++;
        goal->capacity -= 1;
        goal->greenCnt -= 10;
        goal->shape.setFillColor(sf::Color(0, goal->greenCnt, 0));
    }
    if(goal->capacity == 0){
        goal->bee = nullptr;
        goal = nullptr;
        this->inGoal = false;
        this->shape.setRadius(10.f);
        this->shape.setFillColor(sf::Color::Yellow);
        this->shape.setOutlineThickness(0);
    }
}

void Bee::escape() {
    long a = danger_check();
    double dx = this->closest->x - this->x;
    double dy = this->closest->y - this->y;

    double length = sqrt(dx * dx + dy * dy);
    double dx_normalized = dx / length;
    double dy_normalized = dy / length;

    double stepX = -dx_normalized * this->speed;
    double stepY = -dy_normalized * this->speed;

    this->x += stepX;
    this->y += stepY;

    this->shape.move(stepX, stepY);
}

long Bee::danger_check() {
    this->closest = world.hornets[0];
    long min_range = get_distance(*this,*world.hornets[0]);
    for(long i = 1;i<world.hornets.size();++i){
        long curr = get_distance(*this,*world.hornets[i]);
        if(curr<min_range){
            this->closest = world.hornets[i];
            min_range =curr;
        }
    }
    return min_range;
}

void Bee::make_step() {
    std::cout<<"taken: "<<taken<<"\n";
    if(this->indanger!=0){
        this->indanger-=1;
        escape();
    }
    else{
        if(danger_check()<=75){
            std::cout<<"!";
            this->shape.setRadius(10.f);
            this->shape.setFillColor(sf::Color::Yellow);
            this->shape.setOutlineThickness(0);
            this->inGoal=false;
            this->indanger = 10;
        }
        else{
            if ((this->taken >= 10)or(inHive)) {
                if (!inHive) {
                    this->shape.setRadius(10.f);
                    this->shape.setFillColor(sf::Color::Yellow);
                    this->shape.setOutlineThickness(0);
                    if (get_distance(*hive, *this) <= speed) {
                        inHive = set_status(*hive);
                        inGoal = false;
                    } else {
                        this->go_to(*hive);
                    }
                }
                else {
                    if (world.stepNumber % 2 == 0) {
                        if (taken > 0) {
                            taken -= 1;
                            hive->resourses += 1;
                        }
                        else{
                            this->find_goal();
                            inHive = false;
                            shape.setRadius(10.f);
                            shape.setFillColor(sf::Color::Yellow);
                            shape.setOutlineThickness(0);
                        }
                    }
                }
            }
            else if(!inGoal){
                if(world.stepNumber % 10 == 0 || this->goal == nullptr){
                    this->find_goal();
                }
                if(get_distance(*goal, *this) <= speed){
                    inGoal = set_status(*goal);
                }
                else{
                    this->go_to(*goal);
                }
            }
            else{
                if(world.stepNumber % 10 == 0){
                    harvest();
                }
            }
        }
    }
}

Bee::~Bee(){
    auto it = std::find(world.bees.begin(), world.bees.end(), this);
    if (it != world.bees.end()) {
        world.bees.erase(it);
    }

    if (goal != nullptr) {
        goal->busy = false;
        goal->bee = nullptr;
    }

    for(Hornet* hornet : world.hornets){
        if(hornet->goal == this){
            hornet->goal = nullptr;
            hornet->find_goal();
        }
    }
}