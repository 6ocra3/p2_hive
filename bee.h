#include <SFML/Graphics.hpp>
#include "entity.h"
#include "hive.h"

class World;
class Flower;
#ifndef P2_FOREST_15_03_24_BEE_H
#define P2_FOREST_15_03_24_BEE_H

class Bee : public Entity{
public:
    Flower* goal;
    bool inGoal;
    int taken;
    Hive* hive;
    bool inHive;
    Bee(double x, double y, double speed, World& world);
    void make_step() override;
    void find_goal();
    void go_to(Entity& first);
    bool set_status(Entity& first);
    void harvest(Flower& first);
    ~Bee();
};

#endif //P2_FOREST_15_03_24_BEE_H
