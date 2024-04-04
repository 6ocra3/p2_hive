//
// Created by Vadim on 22.02.2024.
//

#ifndef P2_FOREST_15_03_24_HIVE_H
#define P2_FOREST_15_03_24_HIVE_H
#include <SFML/Graphics.hpp>
#include "entity.h"

class World;
class Hive: public Entity{
private:
    virtual void spawn() = 0;
    long long resourses = 0;
    long long needed = 0;
public:
    Hive(double x, double y, double speed, World& world,sf::Color color,int needed);
    void make_step() override;

    long long getResources(){
        return  resourses;
    }

    void setResources(long long resourses){
        this->resourses = resourses;
    }

    void addResources(long long plus){
        this->resourses += plus;
    }


private:

};
#endif //P2_FOREST_15_03_24_HIVE_H
