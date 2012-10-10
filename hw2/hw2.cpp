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


/******************/
/*GLOBAL VARIABLES*/
/******************/

int main_window;

/*stuff from hw1*/
GLfloat x=5.0, y=5.0;
int color = 1;
GLfloat side = 3.0;

/*stuff from hw2*/

float cube_size = 10.0;

float eye_x = 50.0;
float eye_y = 26.375;
float eye_z = 23.41;

float lookat_x;
float lookat_y;
float lookat_z;

float clipping_param;

void display();

GLfloat theta = 15.0495;
/*********/
/*METHODS*/
/*********/

/*Set up window*/
void setupViewport(int w, int h) {

    glClearColor(1.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, w, h); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0.0, XSCALE*w/INITIAL_WIDTH*0.1, 0.0, h*YSCALE/INITIAL_HEIGHT );
}


/*Sets clear color and background color, sets up Viewport*/
void init() {
    glClearColor(1.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 0.0);  /* yellow */
    setupViewport((int)INITIAL_WIDTH*0.8, (int)INITIAL_HEIGHT*0.8);
    //setupViewport(INITIAL_WIDTH, INITIAL_HEIGHT);

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
    int i;
    float alpha;

    glutSetWindow(main_window);
    glClear(GL_COLOR_BUFFER_BIT);

    /*range of grey spectrum*/
    float c;
    float slope;

    for( i = 0; i<8; i++){

	/*set pen color*/
	glColor3f(50,70,90);


	/*draw polygon*/
	/*
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x+side*cos(radians(theta+i*(360.00/8))), y+side*sin(radians(theta+i*(360.00/8))));
	glVertex2f(x+side*cos(radians(theta+(i+1)*(360.00/8))), y+side*sin(radians(theta+(i+1)*(360.00/8))));
	glEnd();
	*/
	/*************/
    }

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

/***************/
/*IDLE FUNCTION*/
/***************/
void spinDisplay() { 
    theta += 0.01*.1;
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
    GLUI_Spinner *cube_size_spinner= new GLUI_Spinner(control_panel, "SIZE", GLUI_SPINNER_FLOAT, &cube_size, 0, cube_size_callback);
    /*cube_size_spinner->set_float_limits(LOWER_COLOR_THRESHOLD, 1.0, GLUI_LIMIT_CLAMP);*/

    /*column 3*/
    new GLUI_Column(control_panel, true);
    /*Eye Position*/
    GLUI_Rollout *eye_position_rollout = new GLUI_Rollout(control_panel, "Eye Position", true );
    /*set x*/
    GLUI_Spinner *eye_x_spinner= new GLUI_Spinner(eye_position_rollout, "X", GLUI_SPINNER_FLOAT, &eye_x, 0, eye_pos_callback);
    /*eye_x_spinner->set_float_limits(LOWER_COLOR_THRESHOLD, 1.0, GLUI_LIMIT_CLAMP);*/
    /*set y*/
    GLUI_Spinner *eye_y_spinner= new GLUI_Spinner(eye_position_rollout, "Y", GLUI_SPINNER_FLOAT, &eye_y, 0, eye_pos_callback);
    /*eye_x_spinner->set_float_limits(LOWER_COLOR_THRESHOLD, 1.0, GLUI_LIMIT_CLAMP);*/
    /*set z*/
    GLUI_Spinner *eye_z_spinner= new GLUI_Spinner(eye_position_rollout, "Z", GLUI_SPINNER_FLOAT, &eye_z, 0, eye_pos_callback);
    /*eye_x_spinner->set_float_limits(LOWER_COLOR_THRESHOLD, 1.0, GLUI_LIMIT_CLAMP);*/

    /*Looking at*/
    GLUI_Rollout *lookat_rollout = new GLUI_Rollout(control_panel, "Looking At", false );
    /*set x*/
    GLUI_Spinner *lookat_x_spinner= new GLUI_Spinner(lookat_rollout, "X", GLUI_SPINNER_FLOAT, &lookat_x, 0, lookat_callback);
    /*eye_x_spinner->set_float_limits(LOWER_COLOR_THRESHOLD, 1.0, GLUI_LIMIT_CLAMP);*/
    /*set y*/
    GLUI_Spinner *lookat_y_spinner= new GLUI_Spinner(lookat_rollout, "Y", GLUI_SPINNER_FLOAT, &lookat_y, 0, lookat_callback);
    /*eye_x_spinner->set_float_limits(LOWER_COLOR_THRESHOLD, 1.0, GLUI_LIMIT_CLAMP);*/
    /*set z*/
    GLUI_Spinner *lookat_z_spinner= new GLUI_Spinner(lookat_rollout, "Z", GLUI_SPINNER_FLOAT, &lookat_z, 0, lookat_callback);
    /*eye_x_spinner->set_float_limits(LOWER_COLOR_THRESHOLD, 1.0, GLUI_LIMIT_CLAMP);*/

    /*column 4*/
    new GLUI_Column(control_panel, true);
    /*clipping parameters*/
    GLUI_Rollout *clipping_rollout = new GLUI_Rollout(control_panel, "Clipping Parameters", false );

    GLUI_Spinner *theta_spinner= new GLUI_Spinner(control_panel, "THETA", GLUI_SPINNER_INT, &theta, 0, theta_callback);
    /*speed_spinner->set_int_limits(0, 10, GLUI_LIMIT_CLAMP);*/

    /*******************/
    /*END USER CONTROLS*/
    /*******************/

    control_panel->set_main_gfx_window(main_window);
    GLUI_Master.set_glutIdleFunc(spinDisplay);
    glutMainLoop();
    return EXIT_SUCCESS;

} 
