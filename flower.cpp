#include "flower.h"
#include "entity.h"
#include "world.h"
#include "utils.cpp"
Flower::Flower(double x, double y, double speed, World& world): greenCnt(100), Entity(x, y, speed, world, sf::Color(0, 100, 0)), capacity(1), busy(
        false), bee(
        nullptr) {
}

void Flower::make_step() {
    if (world.stepNumber % 30 == 0) {
        int chance = randint(1, 10);
        if (chance == 1 && !busy) {
            capacity = 1;
            greenCnt = 100;
            shape.setFillColor(sf::Color(0, greenCnt, 0));
            int xDif = randint(1, 100) - 50;
            int yDif = randint(1, 100) - 50;
            Flower* flower = new Flower(x + xDif, y + yDif, 0, world);
            world.toAddFlowers.push_back(flower);
        } else if (capacity < 10 && !busy) {
            capacity++;
            greenCnt += 10;
            shape.setFillColor(sf::Color(0, greenCnt, 0));
        }
    }
}