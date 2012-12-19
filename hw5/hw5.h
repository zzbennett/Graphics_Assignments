#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/glui.h>

#define BODY 0
#define WING 1
#define DORSAL 2
#define SIDEDORSAL 3

GLfloat body[13][3] = {   {-1.0, 0.0, 0.0},
			    {-1.0, 0.5, 0.0},
			    {-0.5, 1.0, 0.0},
			    {0.0, 1.0, 0.0}, 
			    {0.5, 1.0, 0.0},
			    {1.0, 0.5, 0.0},
			    {1.0, 0.0, 0.0},
			    {1.0, -0.5, 0.0},
			    {0.5, -1.0, 0.0},
			    {0.0, -1.0, 0.0},
			    {-0.5, -1.0, 0.0},
			    {-1.0, -0.5, 0.0},
			    {-1.0, 0.0, 0.0}};

/* Nice wing coordinates*/
GLfloat wing[13][3] = {   {-12.0, 0.0, 0.0},
			    {-1.0, 0.5, 0.0},
			    {-0.5, 1.0, 0.0},
			    {0.0, 1.0, 0.0}, 
			    {0.5, 1.0, 0.0},
			    {1.0, 0.5, 0.0},
			    {1.0, 0.0, 0.0},
			    {1.0, -0.5, 0.0},
			    {0.5, -1.0, 0.0},
			    {0.0, -1.0, 0.0},
			    {-0.5, -1.0, 0.0},
			    {-1.0, -0.5, 0.0},
			    {-12.0, 0.0, 0.0}};

#define N 10 
#define SIZE 3*N+1
GLfloat bodyControlPoints[SIZE][13][3];
GLfloat wingControlPoints[SIZE][13][3];
GLfloat theta = 0.0;

GLfloat *textureMap;
int n, m;

GLuint texID;

/* GLUI variables */
GLfloat X = 10.0;
GLfloat Y = 15.0;
GLfloat Z = 15.0;

int main_window;
