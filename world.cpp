#include "world.h"
#include "flower.h"
#include "bee.h"
#include "hornet.h"
#include <algorithm>
#include "iostream"

World::World(int width, int height): stepNumber(0), width(width), height(height) {

}

void World::check_starvation() {
    for(Hornet* hornet : hornets){
        if(hornet->get_starve()>=85){
            graduating_list.push_back(hornet);
        }
    }
}

void World::draw_world(sf::RenderWindow& window){
    for(Hive* hive:hives){
        window.draw(hive->shape);
    }

    for(Flower* flower : flowers){
        window.draw(flower->shape);
    }

    for(Bee* bee : bees){
        window.draw(bee->shape);
    }

    for(Hornet* hornet : hornets){
        window.draw(hornet->shape);
    }
}

void World::make_step(){
    stepNumber++;
    toAddFlowers.clear();
    std::cout << "Make step: " << stepNumber << "\n";
    if(stepNumber==370){
        std::cout<<"1";
    }
    for(Hive* hive:hives){
        hive->make_step();
    }
    for(Flower* flower : flowers){
        flower->make_step();
    }
//    std::cout << "Flowers have stepped. Flowers left: " << flowers.size() << "\n";

    for(Bee* bee : bees){
        bee->make_step();
    }

    for(Hornet* hornet : hornets){
        hornet->make_step();
    }

    check_starvation();
    for(Hornet* hornet:graduating_list){
        removeHornet(hornet);
    }
    graduating_list.clear();
//    std::cout << "Bees have stepped. Bees left: " << bees.size() << "\n";

//    std::cout << "Hornets have stepped. Hornets left: " << hornets.size() << "\n";
    for(Flower* flower : flowers){
        if(flower->capacity != 0){
            toAddFlowers.push_back(flower);
        }
    }
    flowers.clear();

    for(Flower* flower : toAddFlowers){
        flowers.push_back(flower);
    }
    std::cout << "Number of hornets: " << hornets.size() << "\n";
//    std::cout << stepNumber << " Step finished\n\n\n";
}

void World::removeBee(Bee* bee) {
    delete bee;
}
void World::removeHornet(Hornet* hornet){
    delete hornet;
}