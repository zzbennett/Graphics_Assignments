/* HW4 -- Liz Bennett */
#include "hw4.h"
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
    glRasterPos2i(300-IMAGE_WIDTH/2, 300-IMAGE_HEIGHT/2);  // position of the lower left corner
    // of the bitmap in window coords

    glDrawPixels(IMAGE_WIDTH, IMAGE_HEIGHT, GL_RGB, GL_FLOAT, image);  
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

/* This makes the ray from the viewer through pixel (i,j) */
void MakeRay(int i, int j, Ray *r) {
    GLfloat direction[3];
    GLfloat pixel[3]; // The world coordinates of the (i, j) pixel
    int k;

    copy3(r->point, ViewerPosition);

    //converting pixel into world coordinates
    pixel[0] = GridX;
    pixel[1] = GridY + (GridWidth*j)/IMAGE_WIDTH;
    pixel[2] = GridZ - (GridHeight*i)/IMAGE_HEIGHT;
    for (k = 0; k < 3; k++ ) {
	direction[k] = pixel[k] - r->point[k];
    }
    copy3(r->direction, direction);
    //we just computed r's direction
}

/* TODO intersect ray with Light source */

/* Params:  interestion *i -- the intersection between ray r and i->object
 *	    Ray *r -- the light ray bouncing off the object 
 * Return:  Ray that is the ray from the point of intersection towards the 
 *	    light source */
	    
void MakeLightSourceRay(Intersection *i, Ray *r){
}


/* Takes in a Ray * and an object number, calls appropriate Intersect method */
Intersection *Intersect( Ray *r, Object * object){
    switch( object->ObjectNumber ){
	case POLYGON:
	    return Intersect_Polygon( r, object );
	case SPHERE:
	    return Intersect_Sphere( r, object );
	case LIGHT:
	    return Intersect_light_source( r, object );
	default:
	    return NULL;
    }
}

<<<<<<< HEA
/*copies GLfoat array x of length 3 into GLfloat array y of length 3 */
void copy3(GLfloat *x, GLfloat *y) {
  /* sets x = y */
  int i;
  for (i = 0; i < 3; i++) {
    x[i] = y[i];
  }
======
/* TODO implement me! */
Intersection *Intersect_light_source( Ray *r, Object * object){
>>>>>>> 7fce24161f7d29afc44c862249d4e851a3cf375
}

/* TODO implement me! */
Intersection *Intersect_Polygon( Ray *r, Object * object ) {
}

/* TODO write method for intersections with spheres */
Intersection *Intersect_Sphere( Ray *r, Object * object ) {
}

Intersection *Find_Closest_Intersect( Ray * r ){
    int i;
    Intersection * p = NULL;
    Intersection *cur_p = NULL;
    for(i = 0; i<NUM_OBJECTS; i++){
	//find object with smallest t-value
	p = Intersect( r, Objects[i]);
	if(cur_p != NULL){
	    if(!p || cur_p->t_value < p->t_value )
		p = cur_p;
	}
    }
    return p;
}

GLfloat *Trace(Ray *r, int level, float weight) {
    GLfloat *color = (GLfloat *)malloc(3*sizeof(GLfloat));
    if(level > MAX_RECURSION){
	copy3(color, BLACK);
    }
    else{
	//intersect r with all the objects in the scene
	int i;

	/* TODO make this less jank */
	Intersection *p = Find_Closest_Intersect( r );

	if (p != NULL) {

	    if(trace_finished){
		/* TODO */
		/* Calculate ambient calculation */
		/* Create array from intersection points towards light source */
		/* Create array from intersection point towards light source */
		Ray * l;
		MakeLightSourceRay(p, l);
		p = Find_Closest_Intersect( l );
		if(p->objectNumber == LIGHT){
		    /* we've hit the light source! */
		    //do diffuse calculation
		}

		/*
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


void MakePicture() {  
    // This runs through the pixel grid, makes a ray from the
    // viewer through the pixel, and traces this ray.
    // The pixel gets the color returned by the trace.
    Ray r; /* r is the primary ray */
    int i, j;
    GLfloat *color;

    for (i =0; i < IMAGE_HEIGHT; i++) {
	for (j = 0; j < IMAGE_WIDTH; j++ ) {
	    MakeRay(i, j, &r);
	    color = Trace(&r, 0, 1.0);
	    copy3(image[i][j], color);
	}
    }
}

int main(int argc, char** argv) {
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


