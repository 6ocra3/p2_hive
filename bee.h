#include <SFML/Graphics.hpp>
#include "entity.h"
#include "hive.h"
#include "hornet.h"

class World;
class Flower;
#ifndef P2_FOREST_15_03_24_BEE_H
#define P2_FOREST_15_03_24_BEE_H

class Bee : public Entity{
private:
    Flower* goal;
    bool inGoal;
    int taken;
    bool inHive;
    long indanger = 0;
    Hive* hive;
    Hornet* closest;
public:
    Bee(double x, double y, double speed, World& world,Hive& hive);
    void make_step() override;
    void find_goal();
    bool set_status(Entity& first);
    void harvest();
    long danger_check();
    ~Bee();

    bool get_hive(){
        return inHive;
    };

    void change_closest(Hornet* newClosest){
        this->closest = newClosest;
        if(newClosest == nullptr){
            this->indanger = 0;
        }
    }
    bool compare_closets(Hornet* newClosest){
        return closest == newClosest;
    }
};

#endif //P2_FOREST_15_03_24_BEE_H
