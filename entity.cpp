#include "entity.h"
#include <SFML/Graphics.hpp>

Entity::Entity(double x, double y, double speed, World &world, sf::Color color): x(x), y(y), speed(speed),  world(world) {
    shape.setRadius(10.f);
    shape.setPosition(x, y);
    shape.setFillColor(color);
}