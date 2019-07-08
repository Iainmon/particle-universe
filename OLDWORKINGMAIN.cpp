#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "util.cpp"

#define WIDTH  500
#define HEIGHT 500
#define FPS 60.0f

class Program
{
public:
    Program(unsigned int width, unsigned int height)
    {
    }
    sf::Color getPixel(unsigned int x, unsigned int y)
    {
        return sf::Color(
                util::random(0, 255),
                util::random(0, 255),
                util::random(0, 255)
            );
    }
};

int main()
{

    bool redraw = true;      //Do I redraw everything on the screen?

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
    window.setFramerateLimit(FPS);
    sf::Clock clock;

    sf::Image image;
    image.create(WIDTH, HEIGHT, sf::Color::Black);
    sf::Sprite sprite;
    sf::Texture texture;

    Program program(HEIGHT, WIDTH);

    // Window loop.
    sf::Event event;
    while (window.isOpen()) {
        //Wait until 1/60th of a second has passed, then update everything.
        if (clock.getElapsedTime().asSeconds() >= 1.0f / FPS) {
            redraw = true; //We're ready to redraw everything
            //circle.move(1.0f, 0);
            clock.restart();
        }

        // Handle the user's input
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        //Draw stuff if ready
        if (redraw)
        {
            redraw = false;
            //window.clear(sf::Color(0, 0, 0));

            for (unsigned int x = 0; x < WIDTH; x++)
            {
                for (unsigned int y = 0; y < HEIGHT; y++)
                {
                    image.setPixel(x, y, program.getPixel(x, y));
                }
            }
            texture.loadFromImage(image);
            sprite.setTexture(texture);

            window.draw(sprite);
            window.display();
        }
    }

    return 0;
}
