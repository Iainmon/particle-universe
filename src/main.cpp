#define WIDTH  600
#define HEIGHT 600
#define FPS 30

#define DEBUG 1
#define DEBUG_PHYSICS 1

#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <ctime>
#include <GL/freeglut.h> 
#include <GL/glut.h>
#include <SFML/Graphics.hpp>
#include "util.cpp"
#include "physics/Vector.cpp"
#include "graphics/Graphics.cpp"
#include "drawables/Ball.cpp"

graphics::GraphicHandler* gh;

void updateWrapper() {
    gh->loop();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT
    glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
    glutInitWindowSize(WIDTH, HEIGHT);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner

    gh = new graphics::GraphicHandler();
    gh->setup();

    glutDisplayFunc(updateWrapper); // Register display callback handler for window re-paint
    glutMainLoop();           // Enter the event-processing loop
    return 0;
}

