#include <SFML/Graphics.hpp>
#include "flower.h"
#include "bee.h"
#include "world.h"
#include "hornet.h"
#include <vector>
#include "utils.cpp"
#include "beehive.h"
#include "hornethive.h"
#include "iostream"
#include "globals.h"
std::vector<long> vec;
int main()
{
    long step = 0;
    for(int i = 1000; i<2000;i++){
        step=0;

        global_gen = i;
        sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Application");

        World world(640, 480);

        int x = randint(40, 600);
        int y = randint(40, 440);
        double speed = 0;
        Hive* bhive = new Beehive(x,y,speed,world,sf::Color::Cyan,10);
        world.hives.push_back(bhive);

        x = randint(40, 600);
        y = randint(40, 440);
        speed = 0;
        Hive* horthive = new Hornethive(x,y,speed,world,sf::Color::Magenta,10);
        world.hives.push_back(horthive);

        for(int i = 0; i<40;i++){
            int x = randint(40, 600);
            int y = randint(40, 440);
            int speed = 0;
            Flower* flower = new Flower(x, y, speed, world);
            world.flowers.push_back(flower);
        }
        for(int i = 0; i<15;i++){
            int x = randint(40, 600);
            int y = randint(40, 440);
            double speed = randint(1, 10) / 10 + 4;
            Bee* bee = new Bee(x, y, speed, world,*bhive);
            world.bees.push_back(bee);
        }

        for(int i = 0; i<5;i++){
            int x = randint(40, 600);
            int y = randint(40, 440);
            double speed = randint(1, 10) / 10 + 4.5;
            Hornet* hornet= new Hornet(x, y, speed, world,*horthive);
            world.hornets.push_back(hornet);
        }



        sf::Clock clock;

        while (window.isOpen())
        {
            sf::Event event;
            float stepInterval= 0.0000000001f;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::F3)
                {
                    stepInterval = 0.01f;
                }
                else if (event.key.code == sf::Keyboard::F2)
                {
                    stepInterval = 10000.0f;
                }
                else if (event.key.code == sf::Keyboard::F1)
                {
                    stepInterval = 0.04f;
                }
            }
            if (clock.getElapsedTime().asSeconds() >= stepInterval)
            {
                world.make_step();
                clock.restart();
                step+=1;
            }

            if((world.bees.size()==0) or (world.bees.size()>world.flowers.size()) or (world.hornets.size()==0)){
                break;
            }

            window.clear();
            world.draw_world(window);
            window.display();
        }
        if(step>=3000){
            vec.push_back(i);
            std::cout<<"\n!!!!!!!!!! "<<i<<": "<<step;
        }
        else{
//            std::cout<<"\n"<<i<<": "<<step;
        }
    }
}
//!!!!!!!!!! 43: 4808      0.0000000001f, 4, 4.5
//!!!!!!!!!! 74: 3204       40 15 5
//!!!!!!!!!! 101: 4254
//!!!!!!!!!! 137: 3204
//!!!!!!!!!! 142: 3454