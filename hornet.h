#include <SFML/Graphics.hpp>
#include "entity.h"

class World;
class Bee;

#ifndef P2_FOREST_15_03_24_HORNET_H
#define P2_FOREST_15_03_24_HORNET_H

class Hornet: public Entity{
public:
    Bee* goal;
    Hornet(double x, double y, double speed, World& world);
    void find_goal();
    void make_step() override;
    int stepAttacks;
};

#endif //P2_FOREST_15_03_24_HORNET_H
