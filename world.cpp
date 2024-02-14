#include "world.h"
#include "flower.h"
#include "bee.h"
#include "hornet.h"
#include <algorithm>
World::World(): stepNumber(0) {

}

void World::draw_world(sf::RenderWindow& window){
    for(Flower& flower : flowers){
        window.draw(flower.shape);
    }

    for(Bee& bee : bees){
        window.draw(bee.shape);
    }

    for(Hornet& hornet : hornets){
        window.draw(hornet.shape);
    }
}

void World::make_step(){
    stepNumber++;
    toAddFlowers.clear();
    for(Flower& flower : flowers){
        flower.make_step();
    }
    for(Bee& bee : bees){
        bee.make_step();
    }
    for(Hornet& hornet : hornets){
        hornet.make_step();
    }

    for(Flower& flower : flowers){
        if(flower.capacity != 0){
            toAddFlowers.push_back(flower);
        }
    }

    flowers.clear();

    for(Flower& flower : toAddFlowers){
        flowers.push_back(flower);
    }
}