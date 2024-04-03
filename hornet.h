#include <SFML/Graphics.hpp>
#include "entity.h"

class World;
class Bee;

#ifndef P2_FOREST_15_03_24_HORNET_H
#define P2_FOREST_15_03_24_HORNET_H

class Hornet: public Entity{
public:
    Bee* goal;
    Hornet(double x, double y, double speed, World& world,Hive& hive);
    void find_goal();
    void make_step() override;
    void go_to(Entity& first);
    Hive* hive;
    int stepAttacks;
    bool inhive;
    int taken;
    long starve = 0;
    ~Hornet();
};

#endif //P2_FOREST_15_03_24_HORNET_H
