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
	//glRasterPos2i(300-IMAGE_WIDTH/2, 300-IMAGE_HEIGHT/2);  // position of the lower left corner
	glRasterPos2i(0, 0);  // position of the lower left corner
	// of the bitmap in window coords

	glDrawPixels(IMAGE_WIDTH, IMAGE_HEIGHT, GL_RGB, GL_FLOAT, image);  
	// draws rows 0 to N, cols 0 to M of the bitmap "image".  
	// The bitmap is created below in makeBitmap(), which is 
	// the first function called in the program.

	glFlush();
}

/*copies GLfoat array x of length 3 into GLfloat array y of length 3 */
void copy3(GLfloat *x, GLfloat *y) {
	/* sets x = y */
	int i;
	for (i = 0; i < 3; i++) {
		x[i] = y[i];
	}
}

GLfloat dotProduct(GLfloat * v1, GLfloat * v2){
	GLfloat ret;
	int i;
	for (i = 0; i < 3; i++) {
		ret += v1[i] * v2[i];
	}
	return ret;
}

void printFloat(GLfloat x){
	std::cout << std::fixed << std::setprecision(3) << x << std::endl;
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

void MakeLightSourceRays(Intersection *i, Ray * l[NUM_LIGHTS]){
    GLfloat direction[3];
    int k;
    copy3(l[0]->point, i->point);
    for( k = 0; k<NUM_LIGHTS; k++){
//	    l->direction[0] = pixel[0] - r->point[0];
    }
}


/* Takes in a Ray * and an object number, calls appropriate Intersect method */
Intersection *Intersect( Ray *r, Object * object){
	switch( object->objectNumber ){
		case POLYGON:
			return Intersect_Polygon( r, object );
		case SPHERE:
			return Intersect_Sphere( r, object );
		default:
			return NULL;
	}
}

/* TODO implement me! */
Intersection *Intersect_light_source( Ray *r, Object * object){
}

/* TODO implement me! */
Intersection *Intersect_Polygon( Ray *r, Object * object ) {
}

/* TODO write method for intersections with spheres */
Intersection *Intersect_Sphere( Ray *r, Object * object ) {

	Intersection * intersection = (Intersection *)malloc( sizeof( Intersection ) );

	GLfloat A[3];
	A[0] = object->location[0] - r->point[0];
	A[1] = object->location[1] - r->point[1];
	A[2] = object->location[2] - r->point[2];

	GLfloat vDotA = dotProduct(r->direction, A);
	GLfloat vDotv = dotProduct(r->direction, r->direction);
	GLfloat ADotA = dotProduct(A, A);
	GLfloat squareRoot = 4*(vDotA*vDotA)-(4*vDotv)*(ADotA-(object->radius*object->radius));
	if( squareRoot < 0 ){
	    return NULL;
	}
	else{
	    squareRoot = sqrt(squareRoot);
	}

	GLfloat plus_t = (2*vDotA+squareRoot)/2*vDotv;
	GLfloat minus_t = (2*vDotA-squareRoot)/2*vDotv;

	if(plus_t >= minus_t )
	    intersection->t_value = minus_t;
	else
	    intersection->t_value = plus_t;

	intersection->point[0] = r->point[0]+intersection->t_value*r->direction[0];
	intersection->point[1] = r->point[1]+intersection->t_value*r->direction[1];
	intersection->point[2] = r->point[2]+intersection->t_value*r->direction[2];

	intersection->object = object;
	intersection->objectNumber = object->objectNumber;

	return intersection;
}

Intersection *Find_Closest_Intersect( Ray * r ){
    int i;
    Intersection * smallest_p = NULL;
    Intersection *cur_p = NULL;
    for(i = 0; i<NUM_OBJECTS; i++){
	//find object with smallest t-value
	cur_p = Intersect( r, Objects[i]);
	if(cur_p != NULL ){
	    if(!smallest_p || cur_p->t_value < smallest_p->t_value )
		smallest_p = cur_p;
	}
    }
    return smallest_p;
}

Intersection *Find_Light_Intersects( Ray *rays[NUM_LIGHTS], Intersection * light_intersections[NUM_LIGHTS]){
}

GLfloat *Trace(Ray *r, int level, float weight) {
	GLfloat *color = (GLfloat *)malloc(3*sizeof(GLfloat));
	if(level > MAX_RECURSION){
		copy3(color, BLACK);
	}
	else{
		//intersect r with all the objects in the scene
		int i;

		Intersection *p = Find_Closest_Intersect( r );

		if (p != NULL) {
			if(trace_finished){
				/* TODO */
				/* Calculate ambient calculation */
				/* Create array from intersection point towards light sources */

			    /***************************FIX HERE*******************************/
				Ray *rays[NUM_LIGHTS];
				MakeLightSourceRays(p, rays);
				Intersection * light_intersections[NUM_LIGHTS];
				for(i = 0; i<NUM_LIGHTS; i++){
				    p = Find_Closest_Intersect( rays[i] );
				}
				Intersection * light_intersections[NUM_LIGHTS];
				Find_Light_Intersects( rays, light_intersections );
				//if(p->objectNumber == LIGHT){
					/* we've hit the light source! */
					//do diffuse calculation
				//}

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
			    copy3(color, BLUE);
			}
		}
		else{
			if(level==0)
				copy3(color, BACKGROUND);
			else
				copy3(color, BLACK);
		}
	}
	return color;
}

/* creates all the objects, puts them in the Objects array */
void InitObjects(){
	/* SPHERE */
	Object * sphere = (Object *)malloc( sizeof(Object) );
	sphere->material = &redPlasticMaterials;
	sphere->location[0] = 0.0;
	sphere->location[1] = 0.0;
	sphere->location[2] = 0.0;
	sphere->radius = 3.0;
	sphere->objectNumber = SPHERE;
	Objects[SPHERE] = sphere;

	/* LIGHT 1 */
	Light * light0 = (Light *) malloc( sizeof(Object) );
	light0->light = &lightOne;
	light0->location[0] = 6.0;
	light0->location[1] = 0.0;
	light0->location[2] = 0.0;
	Lights[0] = light0;

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
	InitObjects();
	MakePicture();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Ray Traced Image");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
}


