#define WIDTH 1500.0f
#define HEIGHT 1500.0f
#define FPS 30

#define DEBUG 1
#define DEBUG_PHYSICS 1

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <cmath>
#include <ctime>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <SFML/Graphics.hpp>
#include "util.cpp"
#include "physics/Vector.cpp"
#include "graphics/glDrawing.cpp"
#include "Universe.cpp"
#include "graphics/Graphics.cpp"

graphics::GraphicHandler *gh;

void updateWrapper()
{
    gh->loop();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("The Universe");
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(50, 50);
    
    gh = new graphics::GraphicHandler(new universe::Universe(WIDTH, HEIGHT));
    gh->setup();

    glutIdleFunc(updateWrapper); // Register display callback handler for window re-paint
    glutMainLoop();              // Enter the event-processing loop

    delete gh;

    return 0;
}
