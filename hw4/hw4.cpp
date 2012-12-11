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

/*copies GLfoat array y of length 3 into GLfloat array x of length 3 */
void copy3(GLfloat *x, GLfloat *y) {
    /* sets x = y */
    int i;
    for (i = 0; i < 3; i++) {
	x[i] = y[i];
    }
}

/* normalize the vector given */
void normalize(GLfloat *vector) {
    /* sets x = y */
    int i;
	GLfloat *xyz;
    xyz[0] = vector[0];
	xyz[1] = vector[1];
	xyz[2] = vector[2];
	GLfloat length = sqrt((xyz[0]*xyz[0]) + (xyz[1] * xyz[1]) + (xyz[2] * xyz[2]));
	xyz[0] /= length;
	xyz[1] /= length;
	xyz[2] /= length;
	copy3(vector, xyz);
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
    std::cout << std::fixed << std::setprecision(6) << x << std::endl;
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

void MakeLightSourceRays(Intersection *i, Ray * rays[NUM_LIGHTS]){

    //rays = (Ray **) malloc( NUM_LIGHTS*sizeof( Ray *));

    int k;
	for( k = 0; k<NUM_LIGHTS; k++){
	//	rays[k] = (Ray *) malloc( sizeof( Ray ) );
		copy3(rays[k]->point, i->point);
		rays[k]->direction[0] = Lights[k]->location[0] - rays[k]->point[0];
		rays[k]->direction[1] = Lights[k]->location[1] - rays[k]->point[1];
		rays[k]->direction[2] = Lights[k]->location[2] - rays[k]->point[2];

	}
	/*
	printFloat(rays[0]->point[0]);
	printFloat(rays[0]->point[1]);
	printFloat(rays[0]->point[2]);
	*/
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

	/*Not sure about this, but it fixes my NaN's */
	if(2*vDotv == 0)
		return NULL;
    GLfloat plus_t = ((2*vDotA)+squareRoot)/(2*vDotv);
    GLfloat minus_t = ((2*vDotA)-squareRoot)/(2*vDotv);


    if(plus_t >= minus_t )
	intersection->t_value = minus_t;
    else
	intersection->t_value = plus_t;

	if(intersection->t_value < 0.01)
		return NULL;



    intersection->point[0] = r->point[0]+(intersection->t_value*r->direction[0]);
	//printFloat(intersection->point[0]);
    intersection->point[1] = r->point[1]+(intersection->t_value*r->direction[1]);
	//printFloat(intersection->point[1]);
    intersection->point[2] = r->point[2]+(intersection->t_value*r->direction[2]);
	//printFloat(intersection->point[2]);
	
	intersection->normal[0] = intersection->point[0] - object->location[0];
	intersection->normal[1] = intersection->point[1] - object->location[1];
	intersection->normal[2] = intersection->point[2] - object->location[2];

    intersection->object = object;
    intersection->objectNumber = object->objectNumber;

	//printFloat(intersection->t_value);

    return intersection;
}

Intersection *Find_Closest_Intersect( Ray * r ){
	//printFloat(r->point[0]);
    int i;
    Intersection * smallest_p = NULL;
    Intersection * cur_p = NULL;
	for(i = 0; i<NUM_OBJECTS; i++){
		//find object with smallest t-value
		cur_p = Intersect( r, Objects[i] );
		if(cur_p != NULL ){
			if(!smallest_p || cur_p->t_value < smallest_p->t_value )
				smallest_p = cur_p;
		}
	}
	return smallest_p;
}

Intersection *Find_Light_Intersect( Ray *ray, int light_number){
    Intersection * intersection = (Intersection *)malloc( sizeof( Intersection ) );
    Light * light = Lights[light_number];    

	if(ray->direction[0] == 0 && ray->direction[1] == 0 && ray->direction[2] == 0)
		return NULL;

	GLfloat t_x;
	GLfloat t_y;
	GLfloat t_z;
	GLfloat x = light->location[0];
	GLfloat y = light->location[1];
	GLfloat z = light->location[2];

	t_x = (x - ray->point[0])/ray->direction[0];
	t_y = (y - ray->point[1])/ray->direction[1];
	t_z = (z - ray->point[2])/ray->direction[2];
	//printFloat(t);
	
	if(t_x < 0.01 || t_y < 0.01 || t_z < 0.01)
		return NULL;
	
	printFloat(t_x);
	printFloat(t_y);
	printFloat(t_z);
	/*
	/rintFloat(ray->point[0]);
	printFloat(ray->point[1]);
	printFloat(ray->point[2]);
	printFloat(ray->direction[0]);
	printFloat(ray->direction[1]);
	printFloat(ray->direction[2]);
	*/
	return intersection;
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
	    /* TODO */
	    /* Calculate ambient calculation */
		GLfloat *ambient;
		ambient[0]= p->object->material->ambient[0];
		ambient[1]= p->object->material->ambient[1];
		ambient[2]= p->object->material->ambient[2];

	    /* Create array from intersection point towards light sources */
		
	    Ray ** rays; /* holds array of rays pointing to all the lights*/
		rays = (Ray **) malloc( NUM_LIGHTS*sizeof( Ray *));
		for( i = 0; i<NUM_LIGHTS; i++){
			rays[i] = (Ray *) malloc( sizeof( Ray ) );
		}

	    MakeLightSourceRays(p, rays); /* make those rays */
		Intersection * l;

		for(i = 0; i<NUM_LIGHTS; i++){
		    p = Find_Closest_Intersect( rays[i] );
			if( p != NULL){
				/*
				printFloat( p->point[0] );
				printFloat( p->point[1] );
				printFloat( p->point[2] );
				*/
				//printFloat( p->t_value );
				
			}
			//	printFloat(p->t_value);
		    l = Find_Light_Intersect( rays[i], i ); /*find where ray intersects light*/

			GLfloat *diffuse;
		    if(p == NULL && l == NULL){
			//no diffuse calculation?
		    }
		    else if(p == NULL && l != NULL){
			//we hit the light source, do diffuse calculation
				//diffuse
		    }
		    else if(p != NULL && l == NULL){
			//we hit an object, no diffuse calc
		    }
		    else if(p->t_value < l->t_value){
			//we hit an object, we're in shadow no light calculation
		    }
		    else{ //l->t_value < p->t_value
			//we hit the light source! Diffuse calculation
		    }
			//free( rays[i] );
		}
		/* REFLECTION
		 
		   Ray R = a ray in the reflection direction
		   specular color = Trace(R, level+1, maxlevel)

		   if(object is transparent)
		   Ray T = a ray in the refraction direction
		   Transparent_color = Trace(T, level+1, maxlevel)
		   return ambient_color+diffuse_color+specular_color+transparent_color;
		   */
		copy3(color, ambient);

		for( i = 0; i<NUM_LIGHTS; i++){
			free(rays[i]);
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
    sphere->location[1] = 3.0;
    sphere->location[2] = 0.3;
    sphere->radius = 3.0;
    sphere->objectNumber = SPHERE;
    Objects[SPHERE] = sphere;

    /* LIGHT 1 */
    Light * light0 = (Light *) malloc( sizeof(Object) );
    light0->light = &lightOne;
    light0->location[0] = 2.0;
    light0->location[1] = 1.0;
    light0->location[2] = 10.0;
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


