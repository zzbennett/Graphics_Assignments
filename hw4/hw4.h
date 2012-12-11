#include<GL/glut.h>
#include<cstdio>
#include<stdio.h>
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<math.h>

// N is the height of the bitmap; M is its width
#define IMAGE_HEIGHT 700  //N
#define IMAGE_WIDTH 700  //M

#define MAX_RECURSION 10
#define MIN_WEIGHT 0.01

#define SPHERE 0
#define SPHERE2 1
#define FLOOR 2
#define SIDE_WALL 3
#define BACK_WALL 4
#define POLYGON 5

#define NUM_OBJECTS 2 
#define NUM_LIGHTS 1  //only one light for now

typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;

materialStruct greyPlasticMaterials = {
  {0.3, 0.3, 0.3, 1.0},
  {0.5, 0.5, 0.5, 1.0},
  {0.8, 0.6, 0.6, 1.0},
  30.0};

materialStruct redPlasticMaterials = {
  {0.3, 0.0, 0.0, 1.0},
  {0.9, 0.1, 0.1, 1.0},
  {0.8, 0.6, 0.6, 1.0},
  30.0};

materialStruct greenPlasticMaterials = {
  {0.0, 0.3, 0.0, 1.0},
  {0.0, 0.7, 0.0, 1.0},
  {0.8, 0.6, 0.6, 1.0},
  30.0};

materialStruct bluePlasticMaterials = {
  {0.0, 0.0, 0.3, 1.0},
  {0.0, 0.0, 1.0, 1.0},
  {0.8, 0.6, 0.6, 1.0},
  30.0};

materialStruct yellowPlasticMaterials = {
  {0.3, 0.0, 0.0, 1.0},
  {0.9, 0.8, 0.0, 1.0},
  {0.8, 0.6, 0.6, 1.0},
  30.0};

typedef struct ray {
    GLfloat point[3];
    GLfloat direction[3];
}Ray;

struct lightingStruct {
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
};
typedef struct l {
    struct lightingStruct * light;
    GLfloat location[3];
} Light;

struct lightingStruct lightOne = {
  {0.5, 0.5, 0.5, 1.0},
  {0.8, 0.8, 0.8, 1.0},
  {1.0, 1.0, 1.0, 1.0}};
  

typedef struct object {
    materialStruct * material;
    GLfloat location[3];
    GLfloat radius; // if object is a sphere
    GLfloat A; // if object is a plane
    GLfloat B; // if object is a plane
    GLfloat C; // if object is a plane
    int objectNumber; //ID corresponding to the type of object
} Object;


Object* Objects[NUM_OBJECTS];
Light* Lights[NUM_LIGHTS];


typedef struct intersection {
    GLfloat point[3];
    GLfloat normal[3];
    GLfloat reflection[3];
    int objectNumber;
    Object * object;
    GLfloat t_value;
}Intersection;


//array of intersection functions for each type of object in my scene
//Intersection *(*intersect_methods[NUM_OBJECTS]) (Ray*);
//Object * ObjectsList[NUM_OBJECTS];

GLfloat ViewerPosition[3] = {15.0, 0.0, 0.0};
GLfloat GridX = 10, GridY = -2, GridZ = 3; // Upper left corner pixel grid 
GLfloat GridWidth = 7, GridHeight = 7;  // dimensions of the pixel grid. 
GLfloat PolyWidth = 4, PolyHeight = 4;  // Dimensions of a polygon with one

// vertex at the orign
GLfloat image[IMAGE_HEIGHT][IMAGE_WIDTH][3];			// This is the image bitmap

// colors
GLfloat RED[3] = {1.0, 0.0, 0.0};
GLfloat BLUE[3] = {0.0, 0.0, 1.0};
GLfloat GREEN[3] = {0.0, 1.0, 0.0};
GLfloat BLACK[3] = {0.0, 0.0, 0.0};
GLfloat YELLOW[3] = {1.0, 1.0, 0.0};
GLfloat WHITE[3] = {0.0, 0.0, 0.0};
GLfloat BACKGROUND[3] = {YELLOW[0], YELLOW[1], YELLOW[2]};


void MakeLightSourceRay(Intersection *i, Ray *l);
Intersection *Intersect_light_source( Ray *r, Object * object);
Intersection *Intersect_Polygon( Ray *r, Object * object );
Intersection *Intersect_Sphere( Ray *r, Object * object );

void InitObjects();
