/* Homework 2
 * Liz Bennett
 * Due Oct. 13, 11:59pm
 *
 * Creates a rotating 3D cube using only 2D features of OpenGL
 */

#include<stdio.h>
#include<GL/glut.h>
#include<GL/glui.h>
#include<math.h>

#define true 1
#define false 0
#define INITIAL_WIDTH 500
#define INITIAL_HEIGHT 500
#define XSCALE 10.0
#define YSCALE 10.0
#define PI 3.1415926535
#define SQUARE_OFFSET 0.1


/******************/
/*GLOBAL VARIABLES*/
/******************/

int main_window;

int global_w = INITIAL_WIDTH;
int global_h = INITIAL_HEIGHT;

float cube_size = 10.0;

float eye_x = 50.0;
float eye_y = 26.375;
float eye_z = 23.41;


float lookat_x = 0;
float lookat_y = 0;
float lookat_z = 0;

float clipping_param = 0;
float clipping_yon = 0;
float clipping_hither = 0;

int square_bottom;
int square_top;
int square_left;
int square_right; 


GLfloat theta;
/*********/
/*METHODS*/
/*********/

/*Set up window*/
void setupViewport(int w, int h) {

    square_bottom = (int) h*SQUARE_OFFSET;
    square_top = (int) h-(h*2*SQUARE_OFFSET);
    square_left = (int) w*SQUARE_OFFSET;
    square_right = (int) w-(w*2*SQUARE_OFFSET);

    //glViewport(square_bottom, square_left, square_right, square_top); 
    glViewport(SQUARE_OFFSET*w,SQUARE_OFFSET*h, w-(w*2*SQUARE_OFFSET), h-(h*2*SQUARE_OFFSET)); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(square_left, square_right, square_bottom, square_top);
    //gluOrtho2D(0.0, XSCALE*w/INITIAL_WIDTH*0.1, 0.0, h*YSCALE/INITIAL_HEIGHT );

}


/*Sets clear color and background color, sets up Viewport*/
void init() {

    glClearColor(0.0, 0.8, 0.8, 0.0);
    setupViewport(INITIAL_WIDTH, INITIAL_HEIGHT);

}

/*Called when window gets reshaped*/
void myReshape(int w, int h) {
    setupViewport(w, h);
    glutPostWindowRedisplay(main_window);  
}

/*Convert degrees to radians*/
GLfloat radians(float alpha) {
    return alpha*PI/180.0;
}

/******************/
/*DISPLAY FUNCTION*/
/*Draws the window*/
/******************/
void display(){
    //int i;
    //float alpha;

    glutSetWindow(main_window);
    glClear(GL_COLOR_BUFFER_BIT);


    glColor3f(1.0,0.2,1.0);

    /* square_left = 50
     * square_right = 450
     * square_top = 450
     * square_bottom = 50 */
    glBegin(GL_POLYGON);
    glVertex2f(square_left, square_bottom);
    glVertex2f(square_right, square_bottom);
    glVertex2f(square_right, square_top);
    glVertex2f(square_left, square_top);
    glEnd();

    glColor3f(1.0,0.5,1.0);
    glBegin(GL_POLYGON);
    glVertex2f(square_left+5, square_bottom+5);
    glVertex2f(square_right-5, square_bottom+5);
    glVertex2f(square_right-5, square_top-5);
    glVertex2f(square_left+5, square_top-5);
    glEnd();

    glutSwapBuffers();
}

/*********************/
/*CALL BACK FUNCTIONS*/
/*********************/

/*call back function for sides user control*/
/*void sides_callback(int ID){

    switch (sides_id) {
	case 0:
	    num_sides = 8;
	    break;
	case 1:
	    num_sides = 16;
	    break;
	case 2:
	    num_sides = 32;
	    break;
	case 3:
	    num_sides = 64;
	    break;
	case 4:
	    num_sides = 128;
	    break;
    }

    display();
}*/


/*call back function for eye position  user control*/
void eye_pos_callback(int ID) {

    display();

}

/*call back function for cube size user control*/
void cube_size_callback(int ID) {

    display();

}

/*call back function for look at point user control*/
void lookat_callback(int ID) {

    display();

}

/*call back function for theta user control*/
void theta_callback(int ID) {

    display();

}

/*call back function for theta user control*/
void clipping_callback(int ID) {

    display();

}

/***************/
/*IDLE FUNCTION*/
/***************/
void spinDisplay() { 
    display();
}

int main(int argc, char **argv) {

    /**********************/
    /*INITIALIZATION STUFF*/
    /**********************/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(INITIAL_WIDTH, INITIAL_HEIGHT);
    glutInitWindowPosition(50, 50);
    main_window = glutCreateWindow( "Insane 3D Cube!" );
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(myReshape);

    /***************/
    /*USER CONTROLS*/
    /***************/
    GLUI *control_panel = GLUI_Master.create_glui( "Controls");

    /*column 1*/
    new GLUI_StaticText( control_panel, "Insane Controls" );
    new GLUI_Separator(control_panel);
    new GLUI_Button(control_panel, "Quit", 0, (GLUI_Update_CB)exit);

    /*column 2*/
    new GLUI_Column(control_panel, true);
    /*set cube size*/
    GLUI_Spinner *cube_size_spinner= new GLUI_Spinner(
	    control_panel,
	    "SIZE",
	    GLUI_SPINNER_FLOAT,
	    &cube_size,
	    0,
	    cube_size_callback);
    /*cube_size_spinner->set_float_limits(LOWER_COLOR_THRESHOLD, 1.0, GLUI_LIMIT_CLAMP);*/

    /*column 3*/
    new GLUI_Column(control_panel, true);

    /*Eye Position*/
    GLUI_Rollout *eye_position_rollout = new GLUI_Rollout(
	    control_panel,
	    "Eye Position",
	    true );

    /*set eye_x*/
    GLUI_Spinner *eye_x_spinner= new GLUI_Spinner(
	    eye_position_rollout,
	    "X",
	    GLUI_SPINNER_FLOAT,
	    &eye_x,
	    0,
	    eye_pos_callback);
    /*eye_x_spinner->set_float_limits(LOWER_COLOR_THRESHOLD, 1.0, GLUI_LIMIT_CLAMP);*/

    /*set eye_y*/
    GLUI_Spinner *eye_y_spinner= new GLUI_Spinner(
	    eye_position_rollout,
	    "Y",
	    GLUI_SPINNER_FLOAT,
	    &eye_y,
	    0,
	    eye_pos_callback);
    /*eye_x_spinner->set_float_limits(LOWER_COLOR_THRESHOLD, 1.0, GLUI_LIMIT_CLAMP);*/

    /*set eye_z*/
    GLUI_Spinner *eye_z_spinner= new GLUI_Spinner(
	    eye_position_rollout,
	    "Z",
	    GLUI_SPINNER_FLOAT,
	    &eye_z,
	    0,
	    eye_pos_callback);
    /*eye_x_spinner->set_float_limits(LOWER_COLOR_THRESHOLD, 1.0, GLUI_LIMIT_CLAMP);*/

    /*Looking at*/
    GLUI_Rollout *lookat_rollout = new GLUI_Rollout(
	    control_panel,
	    "Looking At",
	    false );

    /*set lookat_x*/
    GLUI_Spinner *lookat_x_spinner= new GLUI_Spinner(
	    lookat_rollout,
	    "X",
	    GLUI_SPINNER_FLOAT,
	    &lookat_x,
	    0,
	    lookat_callback);
    /*eye_x_spinner->set_float_limits(LOWER_COLOR_THRESHOLD, 1.0, GLUI_LIMIT_CLAMP);*/

    /*set lookat_y*/
    GLUI_Spinner *lookat_y_spinner= new GLUI_Spinner(
	    lookat_rollout,
	    "Y",
	    GLUI_SPINNER_FLOAT,
	    &lookat_y,
	    0,
	    lookat_callback);
    /*eye_x_spinner->set_float_limits(LOWER_COLOR_THRESHOLD, 1.0, GLUI_LIMIT_CLAMP);*/

    /*set lookat_z*/
    GLUI_Spinner *lookat_z_spinner= new GLUI_Spinner(
	    lookat_rollout,
	    "Z",
	    GLUI_SPINNER_FLOAT,
	    &lookat_z,
	    0,
	    lookat_callback);
    /*eye_x_spinner->set_float_limits(LOWER_COLOR_THRESHOLD, 1.0, GLUI_LIMIT_CLAMP);*/

    /*column 4*/
    new GLUI_Column(control_panel, true);
    /*clipping parameters*/
    GLUI_Rollout *clipping_rollout = new GLUI_Rollout(
	    control_panel,
	    "Clipping Parameters",
	    false );
    GLUI_Spinner *clipping_spinner= new GLUI_Spinner(
	    clipping_rollout,
	    "Clip Edges",
	    GLUI_SPINNER_FLOAT,
	    &clipping_param,
	    0,
	    clipping_callback);
    GLUI_Spinner *clipping_yon_spinner= new GLUI_Spinner(
	    clipping_rollout,
	    "Clip Yon Plane",
	    GLUI_SPINNER_FLOAT,
	    &clipping_yon,
	    0,
	    clipping_callback);
    GLUI_Spinner *clipping_hither_spinner= new GLUI_Spinner(
	    clipping_rollout,
	    "Clip Hither Plane",
	    GLUI_SPINNER_FLOAT,
	    &clipping_hither,
	    0,
	    clipping_callback);

    /*set theta*/
    GLUI_Spinner *theta_spinner= new GLUI_Spinner(
	    control_panel,
	    "THETA",
	    GLUI_SPINNER_INT,
	    &theta,
	    0,
	    theta_callback);
    /*speed_spinner->set_int_limits(0, 10, GLUI_LIMIT_CLAMP);*/

    /*******************/
    /*END USER CONTROLS*/
    /*******************/

    control_panel->set_main_gfx_window(main_window);
    GLUI_Master.set_glutIdleFunc(spinDisplay);
    glutMainLoop();
    return EXIT_SUCCESS;

} 
