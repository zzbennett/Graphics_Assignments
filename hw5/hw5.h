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

GLfloat dorsal[13][3] = {   {-5.0, 0.0, 0.0},
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
			    {-5.0, 0.0, 0.0}};

GLfloat side_dorsal[13][3] = {   {-5.0, 0.0, 0.0},
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
			    {-5.0, 0.0, 0.0}};
#define N 10 
#define SIZE 3*N+1
GLfloat bodyControlPoints[SIZE][13][3];
GLfloat wingControlPoints[SIZE][13][3];
GLfloat dorsalControlPoints[SIZE][13][3];
GLfloat sideDorsalControlPoints[SIZE][13][3];
GLfloat theta = 0.0;

GLfloat *textureMap;
int n, m;

GLuint texID;

/* GLUI variables */
/*
GLfloat X = 8.0;
GLfloat Y = 45.0;
GLfloat Z = 8.0;
*/
GLfloat X = -38.0;
GLfloat Y = 2.0;
GLfloat Z = 17.0;

GLUquadricObj *p, *q;  

GLfloat far_z_plane = 1000.0;

int main_window;
