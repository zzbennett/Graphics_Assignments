/* Chapter3/single_double.c  */

/* Portions of this are on p.64 of the Primer.
 * This is the simple spinning square example on p.53, modified
 * to open two windows: one using single-buffering and one using
 * double-buffering.  You can see the improvement given by
 * double-buffering in animation situations.
 */

#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#define DEG_TO_RADIANS M_PI/180.0

int singleb, doubleb;
GLfloat theta = 0.0;

void myinit() {
  glClearColor(1.0, 1.0, 0.0, 0.0);

  glColor3f(1.0, 0.0, 1.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void displays(){
  float a, b;
  a = cos(theta*DEG_TO_RADIANS);
  b = sin(theta*DEG_TO_RADIANS);

  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POLYGON);
  glVertex2f(a, b);
  glVertex2f(-b, a);
  glVertex2f(-a, -b);
  glVertex2f(b, -a);
  glEnd();
  glFlush();
}
 
void displayd(){
  float a, b;
  a = cos(theta*DEG_TO_RADIANS);
  b = sin(theta*DEG_TO_RADIANS);

  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POLYGON);
  glVertex2f(a, b);
  glVertex2f(-b, a);
  glVertex2f(-a, -b);
  glVertex2f(b, -a);
  glEnd();
  glutSwapBuffers();
}

void spinDisplay(void){
  theta += 1.0;
  while (theta > 360.0)
    theta -= 360;
  glutSetWindow(singleb);
  glutPostWindowRedisplay(singleb);
  glutSetWindow(doubleb);
  glutPostWindowRedisplay(doubleb); 
}

void spinDisplayD(void){
  theta += 1.0;
  while (theta > 360.0)
    theta -= 360;
  glutSetWindow(doubleb);
  glutPostWindowRedisplay(doubleb); 
}

void mouse(int btn, int state, int x, int y) {
  if ((btn == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
    glutIdleFunc(NULL);
  else if (btn == GLUT_LEFT_BUTTON)
    glutIdleFunc(spinDisplay);
}

void myReshape(int w, int h) {
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
}


void mykey(unsigned char key, int x, int y) {
  if ( (key == 'Q') || (key == 'q'))
    exit(0);
}

void quit_menu(int id) {
  if (id == 1)
    exit(0);
}


int main(int argc, char **argv) {
  glutInit(&argc, argv);
  
  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  singleb = glutCreateWindow("single buffered" );
  myinit();
  glutDisplayFunc(displays);
  glutReshapeFunc(myReshape);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(310, 0);
  doubleb = glutCreateWindow("double buffered" );
    myinit();
  glutDisplayFunc(displayd);
  glutReshapeFunc(myReshape);

  glutIdleFunc(spinDisplay); 
  glutMouseFunc(mouse); 
  glutCreateMenu(quit_menu);
  glutAddMenuEntry("quit", 1);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutMouseFunc(mouse); 
  glutKeyboardFunc(mykey); 
  
  glutMainLoop();
}
