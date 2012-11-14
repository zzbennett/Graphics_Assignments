#include <GL/glut.h>
#include <GL/glui.h>
 

typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;

materialStruct lightsOn = {
  {0.3, 0.3, 0.3, 1.0},
  {1.0, 1.0, 1.0, 1.0},
  {0.8, 0.6, 0.6, 1.0},
  30.0};

materialStruct lightsOff = {
  {0.3, 0.0, 0.0, 1.0},
  {0.7, 0.6, 0.3, 1.0},
  {0.8, 0.6, 0.6, 1.0},
  30.0};

materialStruct greyPlasticMaterials = {
  {0.3, 0.3, 0.3, 1.0},
  {0.5, 0.5, 0.5, 1.0},
  {0.8, 0.6, 0.6, 1.0},
  30.0};

materialStruct redPlasticMaterials = {
  {0.3, 0.0, 0.0, 1.0},
  {0.9, 0.0, 0.0, 1.0},
  {0.8, 0.6, 0.6, 1.0},
  30.0};

materialStruct greenPlasticMaterials = {
  {0.3, 0.0, 0.0, 1.0},
  {0.0, 1.0, 0.0, 0.1},
  {0.8, 0.6, 0.6, 1.0},
  30.0};

materialStruct bluePlasticMaterials = {
  {0.3, 0.0, 0.0, 1.0},
  {0.0, 0.0, 1.0, 1.0},
  {0.8, 0.6, 0.6, 1.0},
  30.0};

materialStruct yellowPlasticMaterials = {
  {0.3, 0.0, 0.0, 1.0},
  {0.9, 0.8, 0.0, 1.0},
  {0.8, 0.6, 0.6, 1.0},
  30.0};

typedef struct lightingStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
} lightingStruct;

lightingStruct whiteLighting = {
  {0.0, 0.0, 0.0, 1.0},
  {1.0, 1.0, 1.0, 1.0},
  {1.0, 1.0, 1.0, 1.0} };

lightingStruct coloredLighting = {
  {0.2, 0.0, 0.0, 1.0},
  {0.0, 1.0, 0.0, 1.0},
  {0.0, 0.0, 1.0, 1.0} };

GLfloat light0_pos[4] = {4.0, 10.0, 20.0, 0.0};

materialStruct *currentMaterials;
lightingStruct *currentLighting;


GLUquadricObj *p, *q;  

void changeMaterial(materialStruct newMaterial);
void eye_callback(int ID);

/* MY STUFF*/
GLfloat RIGHT_WHEELX = 0.0, RIGHT_WHEELY = 10.0;
GLfloat LEFT_WHEELX = 1.0, LEFT_WHEELY = 10.0;
GLfloat WHEEL_RADIUS = 20.0, WHEEL_WIDTH = 1.0;


int NUM_CARTS = 16;

GLfloat X = 50.0;
GLfloat Y = 5.0;
GLfloat Z = 50.0;

/* for the flashing light pattern */
int flashing = 1;
int ring = 0;

int speed = 5; /*scale from 0 - 10 */
GLfloat spin_theta = 0.0;

int main_window;
