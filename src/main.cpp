#define WIDTH 1000.0f
#define HEIGHT 1000.0f
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
#include "util.cpp"
#include "physics/Vector.cpp"
#include "graphics/glDrawing.cpp"
#include "drawables/NewUniverse.cpp"


void render();

obiectum::DrawableController* dc;

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("The Universe");

    dc = new obiectum::DrawableController();
    ParticleController* particleController = new ParticleController(WIDTH, HEIGHT);
    dc->addObject(particleController);
    dc->addObjects(particleController->particleHierarchy);

    util::init();

    glutIdleFunc(render);
    glutMainLoop();

    return 0;
}

void render()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    glEnable(GL_MULTISAMPLE);

    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0);

    dc->top_call();

    glFlush();
}