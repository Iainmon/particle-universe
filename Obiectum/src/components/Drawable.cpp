#include <iostream>
#include "../Obiectum.hpp"
#include "Components.hpp"

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#include <GL/glut.h>
#endif

using namespace std;
using namespace obiectum;
using namespace components;
using namespace physics;

bool Drawable::isSetup = false;

void Drawable::fcircle(float x, float y, float radius, const Color color = Color::Cyan, const int triangles = 20)
{
   int i;
   int triangleAmount = triangles; //# of triangles used to draw circle

   //GLfloat radius = 0.8f; //radius
   GLfloat twicePi = 2.0f * M_PI;

   glBegin(GL_TRIANGLE_FAN);
   glColor3f(color.r, color.g, color.b);

   glVertex2f(x, y); // center of circle
   for (i = 0; i <= triangleAmount; i++)
   {
      glVertex2f(
          x + (radius * cos(i * twicePi / triangleAmount)),
          y + (radius * sin(i * twicePi / triangleAmount)));
   }
   glEnd();
}

void Drawable::circle(float cx, float cy, float r, int num_segments = 10, const Color color = Color::Cyan)
{

   float theta = 2 * 3.1415926 / float(num_segments);
   float tangetial_factor = tanf(theta); //calculate the tangential factor

   float radial_factor = cosf(theta); //calculate the radial factor

   float x = r; //we start at angle = 0

   float y = 0;

   glBegin(GL_LINE_LOOP);
   glColor3f(color.r, color.g, color.b);
   for (int ii = 0; ii < num_segments; ii++)
   {
      glVertex2f(x + cx, y + cy); //output vertex

      //calculate the tangential vector
      //remember, the radial vector is (x, y)
      //to get the tangential vector we flip those coordinates and negate one of them

      float tx = -y;
      float ty = x;

      //add the tangential vector

      x += tx * tangetial_factor;
      y += ty * tangetial_factor;

      //correct using the radial factor

      x *= radial_factor;
      y *= radial_factor;
   }
   glEnd();
}

Vector2D Drawable::getScreenSize() {
   return physics::Vector2D(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void Drawable::Setup(void)
{
    transform = gameObject->GetComponent<Transform>();
}

void Drawable::Update(void)
{
   Draw();
}

using namespace drawables;


void Circle::Setup(void) {
   detail = 100;
   raidius = 200;
   color = Color::Blue;
   Drawable::Setup();
}

void Circle::Draw(void) {
   fcircle(transform->position.x, transform->position.y, raidius, color, detail);
}