#include <SFML/Graphics.hpp>

class World; // Предварительное объявление класса World

#ifndef P2_FOREST_15_03_24_ENTITY_H
#define P2_FOREST_15_03_24_ENTITY_H

class Entity {
private:
    double x;
    double y;
public:
    double speed;
    World& world;
    sf::CircleShape shape;
    Entity(double x, double y, double speed, World& world, sf::Color color);

    void go_to(Entity& target, int pos=1);

    virtual void make_step() = 0;

    virtual ~Entity()=default;

    double getX() {return x;};
    double getY() {return y;};

    void setX(double x) {
        this->x = x;
        this->shape.setPosition(this->x, this->y);
    };
    void setY(double y) {
        this->y = y;
        this->shape.setPosition(this->x, this->y);
    };
};

#endif //P2_FOREST_15_03_24_ENTITY_H
