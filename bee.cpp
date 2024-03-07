#include "bee.h"
#include "flower.h"
#include "world.h"
#include "utils.cpp"
#include "entity.h"
#include <iostream>
#include "vector"
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

void Bee::make_step() {
    std::cout<<"taken: "<<taken<<"\n";
    if ((this->taken >= 10)or(inHive)) {
//        std::cout<<"to hive\n";
        shape.setRadius(10.f);

        shape.setFillColor(sf::Color::Yellow);
        shape.setOutlineThickness(0);
        if (!inHive) {
//            std::cout<<"1\n";
            if (get_distance(*hive, *this) <= speed) {
                x = hive->x;
                y = hive->y;
                inHive = true;
                shape.setPosition(x, y);
                shape.setRadius(10.f);
                shape.setFillColor(sf::Color::Transparent);
                shape.setOutlineThickness(2.5f);
                shape.setOutlineColor(sf::Color::Yellow);
                return;
            } else {
                double dx = hive->x - this->x;
                double dy = hive->y - this->y;

                double length = sqrt(dx * dx + dy * dy);
                double dx_normalized = dx / length;
                double dy_normalized = dy / length;

                double stepX = dx_normalized * this->speed;
                double stepY = dy_normalized * this->speed;

                this->x += stepX;
                this->y += stepY;

                this->shape.move(stepX, stepY);
                return;
            }
        } else {
//            std::cout<<"2\n";
            if (world.stepNumber % 5 == 0) {
                if (taken > 0) {
                    taken -= 1;
                    hive->honey += 1;
                    return;
                }
                if (taken == 0) {
                    this->find_goal();
                    inHive = false;
                    shape.setRadius(10.f);
                    shape.setFillColor(sf::Color::Yellow);
                    shape.setOutlineThickness(0);
                    return;
                }
            }
            else{
                return;
            }
        }
    }
    if(!inGoal){

        if(world.stepNumber % 10 == 0 || this->goal == nullptr){
            this->find_goal();
        }

        if(get_distance(*goal, *this) <= speed){
            x = goal->x;
            y = goal->y;
            inGoal = true;
            goal->busy = true;
            shape.setPosition(x, y);
            shape.setRadius(10.f);
            shape.setFillColor(sf::Color::Transparent);
            shape.setOutlineThickness(2.5f);
            shape.setOutlineColor(sf::Color::Yellow);
        }
        else{
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
    }
    else{
        if(world.stepNumber % 10 == 0){
            if(goal->capacity > 0){
                taken++;
                goal->capacity -= 1;
                goal->greenCnt -= 10;
                goal->shape.setFillColor(sf::Color(0, goal->greenCnt, 0));
            }
            if(goal->capacity == 0){
                goal->bee = nullptr;
                goal = nullptr;
                inGoal = false;
                shape.setRadius(10.f);
                shape.setFillColor(sf::Color::Yellow);
                shape.setOutlineThickness(0);
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

    for(Hornet& hornet : world.hornets){
        if(hornet.goal == this){
            hornet.goal = nullptr;
            hornet.find_goal();
        }
    }
}