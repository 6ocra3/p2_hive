#include "flower.h"
#include "../entity/entity.h"
#include "../others/world.h"
#include "../others/utils.cpp"
#include "../others/globals.h"
Flower::Flower(double x, double y, double speed, World &world) : greenCnt(100),
                                                                 Entity(x, y, speed, world, sf::Color(0, 100, 0)),
                                                                 capacity(1), busy(
                false), bee(
                nullptr) {
}

void Flower::make_step() {
    if (world.stepNumber % 30 == 0) {
        int chance = randint(1, 10);
        if (chance <= 2 && !busy) {
            for (int i = 0; i < 10; i++) {
                int xDif = randint(1, 200) - 100;
                int yDif = randint(1, 200) - 100;
                int tooClose = 0;
                if(getX()+xDif < 10 || getX()+xDif > world.width-10 || getY()+yDif<10 || getY()+yDif>world.height-10 ){
                    continue;
                }
                Flower *flower = new Flower(getX() + xDif, getY() + yDif, 0, world);
                for (Flower *existFlower: world.flowers) {
                    if (get_distance(*existFlower, *flower) < 20) {
                        tooClose = 1;
                        break;
                    }
                }
                if ((tooClose)or(world.flowers.size()>=80)) {
                    continue;
                }
                capacity = 1;
                greenCnt = 100;
                shape.setFillColor(sf::Color(0, greenCnt, 0));
                world.toAddFlowers.push_back(flower);
                break;
            }
        } else if (capacity < 10 && !busy) {
            capacity++;
            greenCnt += 10;
            shape.setFillColor(sf::Color(0, greenCnt, 0));
        }
    }
}