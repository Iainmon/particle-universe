namespace glDrawing
{

void fcircle(GLfloat x, GLfloat y, GLfloat radius, const sf::Color color = sf::Color::Cyan)
{
   int i;
   int triangleAmount = 20; //# of triangles used to draw circle

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
void circle(float cx, float cy, float r, int num_segments, const sf::Color color = sf::Color::Cyan)
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

physics::Vector2D getScreenSize() {
   return physics::Vector2D(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}
} // namespace glDrawing