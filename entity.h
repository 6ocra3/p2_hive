#include <SFML/Graphics.hpp>

class World; // Предварительное объявление класса World

#ifndef P2_FOREST_15_03_24_ENTITY_H
#define P2_FOREST_15_03_24_ENTITY_H

class Entity {
public:
    double x;
    double y;
    double speed;
    World& world;
    sf::CircleShape shape;
    Entity(double x, double y, double speed, World& world, sf::Color color);

    virtual void make_step() = 0;

    virtual ~Entity() {}
};

#endif //P2_FOREST_15_03_24_ENTITY_H
