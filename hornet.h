#include <SFML/Graphics.hpp>
#include "entity.h"

class World;
class Bee;

#ifndef P2_FOREST_15_03_24_HORNET_H
#define P2_FOREST_15_03_24_HORNET_H

class Hornet: public Entity{
private:
    Hive* hive;
    int stepAttacks;
    bool inhive;
    int taken;
    long starve = 0;
    Bee* goal;
public:
    Hornet(double x, double y, double speed, World& world,Hive& hive);
    void find_goal();
    void make_step() override;
    ~Hornet();

    void change_goal(Bee* newGoal){
        this->goal = newGoal;
    }

    bool compare_goal(Bee* newGoal){
        return newGoal == goal;
    }
    long get_starve(){
        return starve;
    }
};

#endif //P2_FOREST_15_03_24_HORNET_H
