/*     trace.c  */

/* This is a simple non-recursive "ray tracer" */
/* The only object in the scene is a rectangle with */
/* x=0, -2<=y<2, 0<=z<=4.  */


#include <GL/glut.h>
#include <cstdio>

// N is the height of the bitmap; M is its width
#define N 200 
#define M 400 

#define MAX_RECURSION 10
#define MIN_WEIGHT 0.01

#define CUBE 0
#define SPHERE 1
#define LIGHT 2
#define NUM_OBJECTS 2

typedef struct ray {
    GLfloat point[3];
    GLfloat direction[3];
}Ray;

typedef struct intersection {
    GLfloat point[3];
    GLfloat normal[3];
    int objectNumber;
    GLfloat t_value;
}Intersection;

typedef struct lightingStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
} lightingStruct;

GLfloat ViewerPosition[3] = {15.0, 0.0, 2.0};
GLfloat GridX = 10, GridY = -2, GridZ = 3; // Upper left corner pixel grid 

GLfloat GridWidth = 10, GridHeight = 10;  // dimensions of the pixel grid. 

GLfloat PolyWidth = 4, PolyHeight = 4;  // Dimensions of a polygon with one
// vertex at the orign
GLfloat image[N][M][3];			// This is the image bitmap
GLfloat RED[3] = {1.0, 0.0, 0.0};
GLfloat BLUE[3] = {0.0, 0.0, 1.0};
GLfloat GREEN[3] = {0.0, 1.0, 0.0};
GLfloat BLACK[3] = {0.0, 0.0, 0.0};
GLfloat YELLOW[3] = {1.0, 1.0, 0.0};
GLfloat BACKGROUND[3] = {YELLOW[1], YELLOW[2], YELLOW[3]};

//array of intersection functions for each type of object in my scene
Intersection *(*intersect_methods[NUM_OBJECTS+1]) (Ray*);

int trace_finished = 0;

void init() {
    glClearColor(1.0, 1.0, 0.0, 0.0);  // yellow background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 600.0, 0.0, 600.0 );
}

void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLfloat)w, 0.0, (GLfloat)h );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, w, h);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2i(300-M/2, 300-N/2);  // position of the lower left corner
    // of the bitmap in window coords

    glDrawPixels(M, N, GL_RGB, GL_FLOAT, image);  
    // draws rows 0 to N, cols 0 to M of the bitmap "image".  
    // The bitmap is created below in makeBitmap(), which is 
    // the first function called in the program.

    glFlush();
}

void copy3(GLfloat *x, GLfloat *y) {
    /* sets x = y */
    int i;
    for (i = 0; i < 3; i++) {
	x[i] = y[i];
    }
}

void MakeRay(int i, int j, Ray *r) {
    // This makes the ray from the viewer through pixel (i,j)
    GLfloat direction[3];
    GLfloat pixel[3]; // The world coordinates of the (i, j) pixel
    int k;

    copy3(r->point, ViewerPosition);

    //converting pixel into world coordinates
    pixel[0] = GridX;
    pixel[1] = GridY + (GridWidth*j)/M;
    pixel[2] = GridZ - (GridHeight*i)/N;
    for (k = 0; k < 3; k++ ) {
	direction[k] = pixel[k] - r->point[k];
    }
    copy3(r->direction, direction);
    //we just computed r's direction
}

/* TODO intersect ray with Light source */

int MakeLightSourceRay(Intersection *i, Ray *r){
}

Intersection *Intersect_light_source( Ray *r){
    // This returns a non-null value if the ray intersects 
    // our polygon in the y-z plane
    // Your Intersect( ) method will be more complex.

    Intersection *data;
    data->objectNumber = LIGHT;

    // t is the t-value corresponding to x=0.
    GLfloat t = -(r->point[0]/r->direction[0]);

    GLfloat x = 0;
    GLfloat y = r->point[1] + t*r->direction[1];
    GLfloat z = r->point[2] + t*r->direction[2];
    if ( (-PolyWidth/2 <= y) && (y <= PolyWidth/2) && (0 <= z) && (z <= PolyHeight)) {
	data = (Intersection *)malloc( sizeof(Intersection) );
	//calculate the point of intersection
	data->point[0] = x;
	data->point[1] = y;
	data->point[2] = z;
	return data;
    }
    else
	return NULL;
}

Intersection *Intersect_Polygon( Ray *r ) {
    // This returns a non-null value if the ray intersects 
    // our polygon in the y-z plane
    // Your Intersect( ) method will be more complex.

    Intersection *data;
    data->objectNumber = CUBE;

    // t is the t-value corresponding to x=0.
    GLfloat t = -(r->point[0]/r->direction[0]);

    GLfloat x = 0;
    GLfloat y = r->point[1] + t*r->direction[1];
    GLfloat z = r->point[2] + t*r->direction[2];
    if ( (-PolyWidth/2 <= y) && (y <= PolyWidth/2) && (0 <= z) && (z <= PolyHeight)) {
	data = (Intersection *)malloc( sizeof(Intersection) );
	//calculate the point of intersection
	data->point[0] = x;
	data->point[1] = y;
	data->point[2] = z;
	return data;
    }
    else
	return NULL;
}

/* TODO write method for intersections with spheres */
Intersection *Intersect_Sphere( Ray *r ) {
    // This returns a non-null value if the ray intersects 
    // our polygon in the y-z plane
    // Your Intersect( ) method will be more complex.

    Intersection *data;
    data->objectNumber = SPHERE;

    // t is the t-value corresponding to x=0.
    GLfloat t = -(r->point[0]/r->direction[0]);

    GLfloat x = 0;
    GLfloat y = r->point[1] + t*r->direction[1];
    GLfloat z = r->point[2] + t*r->direction[2];
    if ( (-PolyWidth/2 <= y) && (y <= PolyWidth/2) && (0 <= z) && (z <= PolyHeight)) {
	data = (Intersection *)malloc( sizeof(Intersection) );
	//calculate the point of intersection
	data->point[0] = x;
	data->point[1] = y;
	data->point[2] = z;
	return data;
    }
    else
	return NULL;
}

GLfloat *Trace(Ray *r, int level, float weight) {
    GLfloat *color = (GLfloat *)malloc(3*sizeof(GLfloat));
    if(level > MAX_RECURSION){
	copy3(color, BLACK);
    }
    else{
	//intersect r with all the objects in the scene
	int i;
	Intersection *p = NULL;
	Intersection *cur_p = NULL;
	for(i = 0; i<NUM_OBJECTS; i++){
	    //find object with smallest t-value
	    cur_p = intersect_methods[i](r);
	    if(cur_p != NULL){
		if(!p || cur_p->t_value < p->t_value )
		    p = cur_p;
	    }
	}
	if (p != NULL) {

	    if(trace_finished){
		/* TODO */
		/* Calculate ambient calculation */
		/* Create array from intersection points towards light source */
		/* Create array from intersection point towards light source */
		Ray * l;
		MakeLightSourceRay(p, l);

		for(i = 0; i<NUM_OBJECTS; i++){
		    //find object with smallest t-value
		    cur_p = intersect_methods[i](l);
		    if(cur_p != NULL){
			if(!p || cur_p->t_value < p->t_value )
			    p = cur_p;
		    }
		}


		/* Interesct that ray with the scene */
		/*
		   if(it hits light source before an object)
		//do diffuse calculation

		Ray R = a ray in the reflection direction
		specular color = Trace(R, level+1, maxlevel)

		if(object is transparent)
		Ray T = a ray in the refraction direction
		Transparent_color = Trace(T, level+1, maxlevel)
		return ambient_color+diffuse_color+specular_color+transparent_color;
		*/
	    }
	    else{
		if (p->point[1] < 0)
		    copy3(color, RED);
		else if (p->point[1] < 1)
		    copy3(color, GREEN);
		else
		    copy3(color, BLUE);
	    }
	}
	else{
	    if(level==0){
		copy3(color, BACKGROUND);
	    }
	    else{
		copy3(color, BLACK);
	    }
	}
    }
    return color;
}

void InitObjects(){
    intersect_methods[CUBE] = Intersect_Polygon;
    intersect_methods[SPHERE] = Intersect_Sphere;
    intersect_methods[LIGHT] = Intersect_light_source;
}



void MakePicture() {  
    // This runs through the pixel grid, makes a ray from the
    // viewer through the pixel, and traces this ray.
    // The pixel gets the color returned by the trace.
    Ray r;
    int i, j;
    GLfloat *color;

    for (i =0; i < N; i++) {
	for (j = 0; j < M; j++ ) {
	    MakeRay(i, j, &r);
	    color = Trace(&r, 0, 1.0);
	    copy3(image[i][j], color);
	}
    }
}

int main(int argc, char** argv) {
    InitObjects();
    MakePicture();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Ray Traced Image");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}


