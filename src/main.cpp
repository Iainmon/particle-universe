#define WIDTH  600
#define HEIGHT 600
#define FPS 30

#define DEBUG 1
#define DEBUG_PHYSICS 1

#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>
#include "util.cpp"
#include "physics/Vector.cpp"
#include "graphics/Graphics.cpp"
#include "drawables/Ball.cpp"




int main()
{

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

    graphics::Processor processor;
    
    // graphics::Drawable *d1 = new drawables::Ball();
    // graphics::Drawable *d2 = new drawables::Ball();
    // graphics::Drawable *d3 = new drawables::Ball();
    // graphics::Drawable *d4 = new drawables::Ball();
    // graphics::Drawable *d5 = new drawables::Ball();

    // d2->getPosition()->X = WIDTH/2 - 30;
    // d2->getPosition()->Y = HEIGHT/2;

    // d3->getPosition()->X = WIDTH/2 + 60;
    // d3->getPosition()->Y = HEIGHT/2 - 20;

    // d4->getPosition()->X = WIDTH/2 - 100;
    // d4->getPosition()->Y = HEIGHT/2 + 70;

    // d5->getPosition()->X = WIDTH/2 - 100;
    // d5->getPosition()->Y = HEIGHT/2 + 10;

    // processor.loadDrawable(d1);
    // processor.loadDrawable(d2);
    // processor.loadDrawable(d3);
    // processor.loadDrawable(d4);
    // processor.loadDrawable(d5);

    std::vector<graphics::Drawable*> balls;

    for (unsigned int i = 0; i < 2; i++) {
        balls.push_back(new drawables::Ball());
    }

    for (unsigned int i = 0; i < balls.size(); i++) {
        balls[i]->getPosition()->X = i * 100;
        balls[i]->getPosition()->Y = 20;
        balls[i]->setRaidius(50);
        processor.loadDrawable(balls[i]);
    }

    graphics::GraphicHandler gh(&window, processor, FPS);
    gh.setup();
    gh.loop();



    


    return 0;
}
