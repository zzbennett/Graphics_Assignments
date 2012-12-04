#include <GL/glut.h>
#include <cstdio>

// N is the height of the bitmap; M is its width
#define IMAGE_HEIGHT 200  //N
#define IMAGE_WIDTH 400  //M

#define MAX_RECURSION 10
#define MIN_WEIGHT 0.01

#define SPHERE 0
#define POLYGON 1
#define FLOOR 2
#define SIDE_WALL 3
#define BACK_WALL 4
#define LIGHT 5
#define NUM_OBJECTS 1

typedef struct ray {
    GLfloat point[3];
    GLfloat direction[3];
}Ray;

typedef struct object {
    //pointer to a function holding this object's intersection method.
//    Intersection *(*CalcIntersection)(Ray *);
    GLfloat color[3]; //location
    int ObjectNumber;
} Object;

Object* Objects[NUM_OBJECTS];


typedef struct intersection {
    GLfloat point[3];
    GLfloat normal[3];
    int objectNumber;
    Object * object;
    GLfloat t_value;
}Intersection;

typedef struct lightingStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat location[3];
} Light;

//array of intersection functions for each type of object in my scene
//Intersection *(*intersect_methods[NUM_OBJECTS]) (Ray*);
//Object * ObjectsList[NUM_OBJECTS];

GLfloat ViewerPosition[3] = {15.0, 0.0, 2.0};
GLfloat GridX = 10, GridY = -2, GridZ = 3; // Upper left corner pixel grid 
GLfloat GridWidth = 10, GridHeight = 10;  // dimensions of the pixel grid. 
GLfloat PolyWidth = 4, PolyHeight = 4;  // Dimensions of a polygon with one

// vertex at the orign
GLfloat image[IMAGE_HEIGHT][IMAGE_WIDTH][3];			// This is the image bitmap

// colors
GLfloat RED[3] = {1.0, 0.0, 0.0};
GLfloat BLUE[3] = {0.0, 0.0, 1.0};
GLfloat GREEN[3] = {0.0, 1.0, 0.0};
GLfloat BLACK[3] = {0.0, 0.0, 0.0};
GLfloat YELLOW[3] = {1.0, 1.0, 0.0};
GLfloat BACKGROUND[3] = {YELLOW[1], YELLOW[2], YELLOW[3]};


int trace_finished = 0;

void MakeLightSourceRay(Intersection *i, Ray *r);
Intersection *Intersect_light_source( Ray *r, Object * object);
Intersection *Intersect_Polygon( Ray *r, Object * object );
Intersection *Intersect_Sphere( Ray *r, Object * object );

