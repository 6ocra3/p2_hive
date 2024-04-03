#include "entity.h"
#include <SFML/Graphics.hpp>
#include "world.h"

Entity::Entity(double x, double y, double speed, World &world, sf::Color color): x(x), y(y), speed(speed),  world(world) {
    shape.setRadius(10.f);
    shape.setPosition(x, y);
    shape.setFillColor(color);
}

void Entity::go_to(Entity &target, int pos) {
    double dx = target.x - this->x;
    double dy = target.y - this->y;

    if (fabs(dx) > world.width / 2) {
        dx = dx > 0 ? dx - world.width : dx + world.width;
    }
    if (fabs(dy) > world.height / 2) {
        dy = dy > 0 ? dy - world.height : dy + world.height;
    }

    double length = sqrt(dx * dx + dy * dy);
    double dx_normalized = dx / length;
    double dy_normalized = dy / length;

    double stepX = dx_normalized * this->speed * pos;
    double stepY = dy_normalized * this->speed * pos;

    this->x += stepX;
    if (this->x < 0) this->x += world.width;
    if (this->x >= world.width) this->x -= world.width;

    this->y += stepY;
    if (this->y < 0) this->y += world.height;
    if (this->y >= world.height) this->y -= world.height;

    this->shape.setPosition(this->x, this->y);

}