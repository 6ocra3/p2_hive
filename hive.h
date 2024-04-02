//
// Created by Vadim on 22.02.2024.
//

#ifndef P2_FOREST_15_03_24_HIVE_H
#define P2_FOREST_15_03_24_HIVE_H
#include <SFML/Graphics.hpp>
#include "entity.h"

class World;
class Hive: public Entity{
public:
    Hive(double x, double y, double speed, World& world,sf::Color color,int needed);
    void make_step() override;
    virtual void spawn() = 0;
    long long resourses = 0;
    long long needed = 0;
private:

};
#endif //P2_FOREST_15_03_24_HIVE_H
