#include <SFML/Graphics.hpp>
#include <vector>
#include <stdio.h>
#include <iostream>

namespace graphics
{

class GraphicHandler
{
private:

    unsigned long long lastTime = util::micros();
    universe::Universe *universe;

public:
    GraphicHandler(universe::Universe *_universe)
    {
        universe = _universe;
    }
    ~GraphicHandler() {
        delete universe;
    }
    void setup()
    {
        // const unsigned int width = glutGet(GLUT_WINDOW_WIDTH);
        // const unsigned int height = glutGet(GLUT_WINDOW_HEIGHT);
        util::init();
    }

    void loop()
    {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque

        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glutSetOption(GLUT_MULTISAMPLE, 8);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
        glEnable( GL_MULTISAMPLE );

        gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0);

        const unsigned long long now = util::micros();
        const float deltaTime = ((float)( (now - lastTime)  / 1000)) / 100;
        lastTime = now;

        universe->Draw(deltaTime);

        glFlush();
    }
};
} // namespace graphics