#include "bee.h"
#include "flower.h"
#include "entity.h"
#include <random>
#include "world.h"
#include "globals.h"

inline double get_distance(Entity& first, Entity& second){
    double dx = fabs(first.getX() - second.getX());
    double dy = fabs(first.getY() - second.getY());

    if (dx > first.world.width / 2.0) {
        dx = first.world.width - dx;
    }
    if (dy > first.world.height / 2.0) {
        dy = first.world.height - dy;
    }

    return sqrt(dx * dx + dy * dy);
}

inline int randint(int start, int end){
//    std::random_device rd;
//    std::default_random_engine generator(global_gen);
//    static std::mt19937 gen(rd());
    static std::mt19937 gen(global_gen);

    std::uniform_int_distribution<> distrib(start, end);
    return distrib(gen);
}