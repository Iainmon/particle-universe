#define WIDTH  600
#define HEIGHT 600
#define FPS 30

#define DEBUG 1
#define DEBUG_PHYSICS 1

#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <GL/freeglut.h> 
#include <GL/glut.h>
#include <SFML/Graphics.hpp>
#include "util.cpp"
#include "physics/Vector.cpp"
#include "graphics/Graphics.cpp"
#include "drawables/Ball.cpp"


int main()
{

    graphics::GraphicHandler gh = graphics::GraphicHandler();

    gh.setup();

    return 0;
}

