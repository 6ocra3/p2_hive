#include "bee.h"
#include "flower.h"
#include "entity.h"
#include <random>

inline double get_distance(Entity& first, Entity& second){
    double x = first.x - second.x;
    double y = first.y - second.y;
    return sqrt((x*x) + (y*y));
}

inline int randint(int start, int end){
    std::random_device rd;
//    static std::mt19937 gen(rd());
    static std::mt19937 gen(127);

    std::uniform_int_distribution<> distrib(start, end);
    return distrib(gen); // Используем глобальный генератор
}