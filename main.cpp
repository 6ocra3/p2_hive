#include <SFML/Graphics.hpp>
#include "flower/flower.h"
#include "bee/bee.h"
#include "others/world.h"
#include "hornet/hornet.h"
#include <vector>
#include "others/utils.cpp"
#include "hive/beehive.h"
#include "hive/hornethive.h"
#include "iostream"
#include "others/globals.h"
std::vector<long> vec;
int main()
{
    long step = 0;
    for(int k = 0;k<1000;++k) {
        step=0;
        global_gen = k;
        sf::RenderWindow window(sf::VideoMode(1440, 900), "SFML Application");
        World world(1440, 900);
        global_gen = k;
        for (int i = 0; i < 75; i++) {
            int x = randint(40, 1400);
            int y = randint(40, 860);
            int speed = 0;
            Flower *flower = new Flower(x, y, speed, world);
            world.flowers.push_back(flower);
        }
        for (int j = 0; j < 3; ++j) {
            int x = randint(40, 1400);
            int y = randint(40, 860);
            double speed = 0;
            Hive *bhive = new Beehive(x, y, speed, world, sf::Color::Cyan, 10);
            world.hives.push_back(bhive);
            for (int i = 0; i < 15; i++) {
                int x = randint(40, 1400);
                int y = randint(40, 860);
                double speed = randint(1, 10) / 10 + 4;
                Bee *bee = new Bee(x, y, speed, world, *bhive);
                world.bees.push_back(bee);
            }
        }

        for (int j = 0; j < 3; ++j) {
            int x = randint(40, 1400);
            int y = randint(40, 860);
            int speed = 0;
            Hive *horthive = new Hornethive(x, y, speed, world, sf::Color::Magenta, 10);
            world.hives.push_back(horthive);
            for (int i = 0; i < 5; i++) {
                int x = randint(40, 1400);
                int y = randint(40, 860);
                double speed = randint(1, 10) / 10 + 4.5;
                Hornet *hornet = new Hornet(x, y, speed, world, *horthive);
                world.hornets.push_back(hornet);
            }
        }

        sf::Clock clock;
        while (window.isOpen()) {
            sf::Event event;
            float stepInterval = 0.000000001;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::F3) {
                    stepInterval = 0.01f;
                } else if (event.key.code == sf::Keyboard::F2) {
                    stepInterval = 10000.0f;
                } else if (event.key.code == sf::Keyboard::F1) {
                    stepInterval = 0.04f;
                }
            }
            if (clock.getElapsedTime().asSeconds() >= stepInterval) {
                world.make_step();
                clock.restart();
                step += 1;
            }

            if ((world.bees.size() == 0) or (world.bees.size() > world.flowers.size()) or (world.hornets.size() == 0)) {
                break;
            }
            if(step>=3000){
                break;
            }
            window.clear();
            world.draw_world(window);
            window.display();
        }
        std::cout<<"\n"<<k<<" "<<step;
    }
}
//!!!!!!!!!! 43: 4808      0.0000000001f, 4, 4.5
//!!!!!!!!!! 74: 3204       40 15 5
//!!!!!!!!!! 101: 4254
//!!!!!!!!!! 137: 3204
//!!!!!!!!!! 142: 3454
//!!!!!!!!!! 1013: 3958
//!!!!!!!!!! 1243: 3274
//!!!!!!!!!! 1302: 4919
//!!!!!!!!!! 1329: 6374
//!!!!!!!!!! 0: 5028
//!!!!!!!!!! 21: 10574