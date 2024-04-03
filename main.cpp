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
int main()
{
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

    for(int i = 0; i<20;i++){
        int x = randint(40, 600);
        int y = randint(40, 440);
        int speed = 0;
        Flower* flower = new Flower(x, y, speed, world);
        world.flowers.push_back(flower);
    }
    for(int i = 0; i<8;i++){
        int x = randint(40, 600);
        int y = randint(40, 440);
        double speed = randint(1, 8) / 10 + 1;
        speed = 6;
        Bee* bee = new Bee(x, y, speed, world,*bhive);
        world.bees.push_back(bee);
    }

    for(int i = 0; i<5;i++){
        int x = randint(40, 600);
        int y = randint(40, 440);
        double speed = randint(1, 8) / 10 + 0.6;
        speed = 3;
        Hornet* hornet= new Hornet(x, y, speed, world,*horthive);
        world.hornets.push_back(hornet);
    }



    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (clock.getElapsedTime().asSeconds() >= 0.06f)
        {
            world.make_step();
            clock.restart();
        }

        window.clear();
        world.draw_world(window);
        window.display();
    }
}