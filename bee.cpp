#include "bee.h"
#include "flower.h"
#include "world.h"
#include "utils.cpp"
#include "entity.h"
#include <iostream>
#include "vector"
Bee::Bee(double x, double y, double speed, World& world): Entity(x, y, speed, world, sf::Color::Yellow), goal(nullptr), taken(0), inGoal(
        false){}

void Bee::find_goal(){
    std::vector < std::pair< double, Flower*  > > closestFlowers;
    for(Flower& flower : world.flowers){
        std::pair< double, Flower* > newPair;
        newPair.first = get_distance(*this, flower);
        newPair.second = &flower;
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
            prevBee->find_goal();
        }
    }

}

void Bee::make_step() {
    if(!inGoal){

        if(world.stepNumber % 10 == 0 || this->goal == nullptr){
            this->find_goal();
        }

        if(get_distance(*goal, *this) <= speed){
            std::cout << 1;
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
