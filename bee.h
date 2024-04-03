#include <SFML/Graphics.hpp>
#include "entity.h"
#include "hive.h"
#include "hornet.h"

class World;
class Flower;
#ifndef P2_FOREST_15_03_24_BEE_H
#define P2_FOREST_15_03_24_BEE_H

class Bee : public Entity{
public:
    Flower* goal;
    bool inGoal;
    int taken;
    bool inHive;
    Bee(double x, double y, double speed, World& world,Hive& hive);
    Hive* hive;
    Hornet* closest;
    void make_step() override;
    void find_goal();
    void go_to(Entity& first);
    bool set_status(Entity& first);
    void harvest();
    void escape();
    long danger_check();
    long indanger = 0;
    ~Bee();
};

#endif //P2_FOREST_15_03_24_BEE_H
