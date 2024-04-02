#include "bee.h"
#include "flower.h"
#include "world.h"
#include "utils.cpp"
#include "entity.h"
#include <iostream>
#include "vector"
#include "beehive.h"
Bee::Bee(double x, double y, double speed, World& world): Entity(x, y, speed, world, sf::Color::Yellow), goal(nullptr), taken(0), inGoal(
        false),inHive(false),hive(world.hives[0]){}
void Bee::find_goal(){
    if(this->goal != nullptr){
        this->goal->bee = nullptr;
        this->goal = nullptr;
    }
    std::vector < std::pair< double, Flower*  > > closestFlowers;
    for(Flower* flower : world.flowers){
        std::pair< double, Flower* > newPair;
        newPair.first = get_distance(*this, *flower);
        newPair.second = flower;
        closestFlowers.push_back(newPair);
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

void Bee::harvest(Flower &first) {
    if(first.capacity > 0){
        this->taken++;
        first.capacity -= 1;
        first.greenCnt -= 10;
        first.shape.setFillColor(sf::Color(0, first.greenCnt, 0));
    }
    if(first.capacity == 0){
        first.bee = nullptr;
        this->goal = nullptr;
        this->inGoal = false;
        this->shape.setRadius(10.f);
        this->shape.setFillColor(sf::Color::Yellow);
        this->shape.setOutlineThickness(0);
    }
}

void Bee::make_step() {
    std::cout<<"taken: "<<taken<<"\n";
    if ((this->taken >= 10)or(inHive)) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::Yellow);
        shape.setOutlineThickness(0);
        if (!inHive) {
            if (get_distance(*hive, *this) <= speed) {
                inHive = set_status(*hive);
            } else {
                this->go_to(*hive);
            }
        }
        else {
            if (world.stepNumber % 5 == 0) {
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
            harvest(*goal);
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

    for(Hornet& hornet : world.hornets){
        if(hornet.goal == this){
            hornet.goal = nullptr;
            hornet.find_goal();
        }
    }
}