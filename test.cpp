#include <GL/freeglut.h> 
#include <stdlib.h> 

#include <GL/glut.h>  // GLUT, include glu.h and gl.h
 
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque 

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( 0.0, 500.0, 500.0,0.0 );

	glBegin(GL_POINTS);
 	  glColor3f(255, 0, 0);
 	  glVertex2i(10, 5);
	glEnd();
 
   	glFlush();  // Render now
}
 
/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT
    glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
    glutInitWindowSize(320, 320);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutDisplayFunc(display); // Register display callback handler for window re-paint
    glutMainLoop();           // Enter the event-processing loop
    return 0;
}