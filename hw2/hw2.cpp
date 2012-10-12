/* Homework 2
 * Liz Bennett
 * Due Oct. 13, 11:59pm
 *
 * Creates a rotating 3D cube using only 2D features of OpenGL
 */

#include"hw2.h"

/*********/
/*METHODS*/
/*********/

/*Set up window*/
void setupViewport(int w, int h) {

    /*square bottom and square left are 0, 0*/
    square_top = (int) h-(h*2*SQUARE_OFFSET) - h*SQUARE_OFFSET;
    square_right = (int) w-(w*2*SQUARE_OFFSET) - w*SQUARE_OFFSET;

    //glViewport(square_bottom, square_left, square_right, square_top); 
    glViewport(SQUARE_OFFSET*w,SQUARE_OFFSET*h, w-(w*2*SQUARE_OFFSET), h-(h*2*SQUARE_OFFSET)); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, square_right, 0, square_top);
    //gluOrtho2D(0.0, XSCALE*w/INITIAL_WIDTH*0.1, 0.0, h*YSCALE/INITIAL_HEIGHT );

}


/*Sets clear color and background color, sets up Viewport*/
void init() {

    glClearColor(0.0, 0.8, 0.8, 0.0);
    setupViewport(INITIAL_WIDTH, INITIAL_HEIGHT);

}

/*Called when window gets reshaped*/
void myReshape(int w, int h) {
    calc_w_matrix();
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
    glutSetWindow(main_window);
    glClear(GL_COLOR_BUFFER_BIT);


    /******************/
    /*Drawing viewport*/
    /******************/
    glColor3f(1.0,0.2,1.0);

    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(square_right, 0);
    glVertex2f(square_right, square_top);
    glVertex2f(0, square_top);
    glEnd();

    glColor3f(1.0,0.5,1.0);
    glBegin(GL_POLYGON);
    glVertex2f(5, 5);
    glVertex2f(square_right-5, 5);
    glVertex2f(square_right-5, square_top-5);
    glVertex2f(5, square_top-5);
    glEnd();

    /******************
     * Drawing Lines *
     * ***************/

    glutSwapBuffers();
}

/*********************/
/*CALL BACK FUNCTIONS*/
/*********************/


/*call back function for eye position  user control*/
void eye_pos_callback(int ID) {

    calc_v_matrix();
    display();

}

/*call back function for cube size user control*/
void cube_size_callback(int ID) {

    /*adjust vertices*/
    vertices[1][1] = cube_size; /*1*/
    vertices[2][0] = cube_size; /*2*/
    vertices[3][0] = cube_size; /*3*/
    vertices[3][1] = cube_size; /*3*/
    vertices[4][2] = cube_size; /*4*/
    vertices[5][1] = cube_size; /*5*/
    vertices[5][2] = cube_size; /*5*/
    vertices[6][0] = cube_size; /*6*/
    vertices[6][2] = cube_size; /*6*/
    vertices[7][0] = cube_size; /*7*/
    vertices[7][1] = cube_size; /*7*/
    vertices[7][2] = cube_size; /*7*/
    display();

}

/*call back function for look at point user control*/
void lookat_callback(int ID) {

    calc_v_matrix();
    display();

}

/*call back function for theta user control*/
void theta_callback(int ID) {

    display();

}

/*call back function for theta user control*/
void clipping_callback(int ID) {

    calc_p_matrix();
    display();

}

/***************/
/*IDLE FUNCTION*/
/***************/
void spinDisplay() { 
}

/***********************/
/*MATRIX TRANSFORMATION*/
/***********************/

/*Take in two matrices, return the resultant matrix*/
int** MultiplyMatrices(int** matrix_1, int** matrix_2){

    int** ret;
    return ret;
}

int** homogenize(int** input){

    int** ret;
    return ret;
}

void calc_v_matrix(){


    int** ret;
    Matrix* mat;
    v_matrix = mat;
}

void calc_p_matrix(){

    int** ret;
    p_matrix = ret;
}

void calc_w_matrix(){

    int** ret;
    w_matrix = ret;
}

int** FullViewPipeLine(int** input_coordinates ){
    int** output = 
	MultiplyMatrices( input_coordinates, 
	    MultiplyMatrices(v_matrix, 
		MultiplyMatrices(p_matrix, w_matrix)));
    output = homogenize(output);
    return output;
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
