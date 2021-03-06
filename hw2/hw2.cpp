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
    square_top = (int) h-(h*SQUARE_OFFSET);
    square_right = (int) w-(w*SQUARE_OFFSET);
    square_bottom = (int) (SQUARE_OFFSET*w);
    square_left = (int) (SQUARE_OFFSET*h);

    //glViewport(square_bottom, square_left, square_right, square_top); 
    glViewport(0, 0, w, h); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    //gluOrtho2D(0.0, XSCALE*w/INITIAL_WIDTH*0.1, 0.0, h*YSCALE/INITIAL_HEIGHT );

}


/*Sets clear color and background color, sets up Viewport*/
void init() {

   v_matrix = new Matrix();
   calc_v_matrix();

   p_matrix = new Matrix();
   calc_p_matrix();

   w_matrix = new Matrix();
   calc_w_matrix();

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
    glVertex2f(square_left, square_bottom);
    glVertex2f(square_right, square_bottom);
    glVertex2f(square_right, square_top);
    glVertex2f(square_left, square_top);
    glEnd();

    glColor3f(1.0,0.5,1.0);
    glBegin(GL_POLYGON);
    glVertex2f((square_left+clipping_param), (square_bottom+clipping_param));
    glVertex2f((square_right-clipping_param), (square_bottom+clipping_param));
    glVertex2f((square_right-clipping_param), (square_top-clipping_param));
    glVertex2f((square_left+clipping_param), (square_top-clipping_param));
    glEnd();

    /****************
     * Drawing Cube *
     * *************/

    draw_line(vertices[0], vertices[1], 0.5,0.7,0.7);
    draw_line(vertices[0], vertices[2], 0.5,0.7,0.7);
    draw_line(vertices[0], vertices[4], 0.5,0.7,0.7);
    draw_line(vertices[1], vertices[3], 0.7,0.9,0.9);
    draw_line(vertices[1], vertices[5], 0.6,0.8,0.8);
    draw_line(vertices[2], vertices[3], 0.7,0.9,0.9);
    draw_line(vertices[2], vertices[6], 0.6,0.8,0.8);
    draw_line(vertices[3], vertices[7], 0.8,1.0,1.0);
    draw_line(vertices[4], vertices[5], 0.6,0.8,0.8);
    draw_line(vertices[4], vertices[6], 0.6,0.8,0.8);
    draw_line(vertices[1], vertices[7], 0.9,1.0,1.0);
    draw_line(vertices[5], vertices[7], 1.0,1.0,1.0);
    draw_line(vertices[6], vertices[7], 1.0,1.0,1.0);


    glutSwapBuffers();

}

void draw_line(float v_1[3], float v_2[3], float r, float g, float b){

    glColor3f(r, g, b);

    Matrix* m1 = new Matrix();
    float v1_vector[4] ;
    v1_vector[0] = v_1[0];
    v1_vector[1] = v_1[1];
    v1_vector[2] = v_1[2];
    v1_vector[3] = 1;
    m1 ->Vector( v1_vector );
    m1 = FullViewPipeLine(m1);

    Matrix* m2 = new Matrix();
    float v2_vector[4] ;
    v2_vector[0] = v_2[0];
    v2_vector[1] = v_2[1];
    v2_vector[2] = v_2[2];
    v2_vector[3] = 1;
    m2->Vector( v2_vector );
    m2 = FullViewPipeLine(m2);

    Matrix* clipped_line = new Matrix();

    clipped_line->Line(m1, m2);

    clipped_line = clip_edges(clipped_line);

    if(!clipped_line->isEmpty){
    glBegin(GL_LINES);
    glVertex2f(clipped_line->elements[0][0], clipped_line->elements[0][1]);
    glVertex2f(clipped_line->elements[1][0], clipped_line->elements[1][1]);
    glEnd();
    }

}

Matrix* clip_edges(Matrix* line){
    line = check_line_for_clipping(line, HITHER);
    line = check_line_for_clipping(line, YON);
    line = check_line_for_clipping(line, LEFT);
    line = check_line_for_clipping(line, TOP);
    line = check_line_for_clipping(line, RIGHT);
    line = check_line_for_clipping(line, BOTTOM);
    return line;
}
Matrix* check_line_for_clipping(Matrix* line, int plane){
    if(line->isEmpty)
	return line;
    float v1[3] = {line->elements[0][0], line->elements[0][1], line->elements[0][2]};
    float v2[3] = {line->elements[1][0], line->elements[1][1], line->elements[1][2]};

    //the line is off the screen
    if(is_clipped(v1, plane) && is_clipped(v2, plane)){
	line = new Matrix();
	return line;
    }
    //the line is partially on the screen
    if(is_clipped(v1, plane) ^ is_clipped(v2, plane)){
	//find intersection of line and edge
	//if v2 is off the screen, flip v1 and v2
	if(is_clipped(v2, plane)){
	    float temp[3] = {v2[0], v2[1], v2[2]};
	    v2[0] = v1[0];
	    v2[1] = v1[1];
	    v2[2] = v1[2];

	    v1[0] = temp[0];
	    v1[1] = temp[1];
	    v1[2] = temp[2];
	}

	puts("before find_intersection");
	line->ToString();
	line = find_intersection(v1, v2, plane);
	puts("after find_intersection");
	line->ToString();

	return line;

    }
    //the line is on the screen
    if(!(is_clipped(v1, plane) && is_clipped(v2, plane) )){
	return line;
    }
}

int is_clipped(float v[3], int plane){
    switch(plane){
	case LEFT:
	    if(v[0] < square_left+clipping_param )
		return 1;
	    break;
	case RIGHT:
	    if(v[0] > square_right-clipping_param)
		return 1;
	    break;
	case BOTTOM:
	    if(v[1] < square_bottom+clipping_param)
		return 1;
	    break;
	case TOP:
	    if(v[1] > square_top-clipping_param)
		return 1;
	    break;
	case YON:
	    if(v[2] > 1){
		return 1;
	    }
	    break;
	case HITHER:
	    if(v[2] < 0){
		return 1;
	    }
	    break;
    }
    return 0;
}

Matrix* find_intersection(float v1[4], float v2[4], int plane){
    Matrix* line = new Matrix();
    float t;

    float p0_x = v1[0];
    float p0_y = v1[1];
    float p0_z = v1[2];

    float v_x = v2[0]-v1[0];
    float v_y = v2[1]-v1[1];
    float v_z = v2[2]-v1[2];

    float new_x;
    float new_y;
    float new_z;


    switch(plane){
	case LEFT:
	    t = ((square_left+clipping_param)-p0_x)/v_x;
	    new_x = square_left+clipping_param;
	    new_y = p0_y + v_y*t;
	    new_z = p0_z + v_z*t;
	    v1[0] = new_x;
	    v1[1] = new_y;
	    v1[2] = new_z;
	    line->Line(v1, v2);
	    break;
	case RIGHT:
	    t = ((square_right-clipping_param)-p0_x)/v_x;
	    new_x = square_right-clipping_param;
	    new_y = p0_y + v_y*t;
	    new_z = p0_z + v_z*t;
	    v1[0] = new_x;
	    v1[1] = new_y;
	    v1[2] = new_z;
	    line->Line(v1, v2);
	    break;
	case BOTTOM:
	    t = ((square_bottom+clipping_param)-p0_y)/v_y;
	    new_x = p0_x + v_x*t;
	    new_y = square_bottom+clipping_param;
	    new_z = p0_z + v_z*t;
	    v1[0] = new_x;
	    v1[1] = new_y;
	    v1[2] = new_z;
	    line->Line(v1, v2);
	    break;
	case TOP:
	    t = ((square_top-clipping_param)-p0_y)/v_y;
	    new_x = p0_x + v_x*t;
	    new_y = square_top-clipping_param;
	    new_z = p0_z + v_z*t;
	    v1[0] = new_x;
	    v1[1] = new_y;
	    v1[2] = new_z;
	    line->Line(v1, v2);
	    break;
	case YON:
	    t = (1-p0_z)/v_z;
	    printf("clipping yon!! t is %f\n", t);
	    new_x = p0_x + v_x*t;
	    new_y = p0_y + v_y*t;
	    new_z = 1;
	    v1[0] = new_x;
	    v1[1] = new_y;
	    v1[2] = new_z;
	    line->Line(v1, v2);
	    break;
	case HITHER:
	    t = (0-p0_z)/v_z;
	    new_x = p0_x + v_x*t;
	    new_y = p0_y + v_y*t;
	    new_z = 0;
	    v1[0] = new_x;
	    v1[1] = new_y;
	    v1[2] = new_z;
	    line->Line(v1, v2);
	    break;
    }

    return line;
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
/*int** MultiplyMatrices(int** matrix_1, int** matrix_2){

    int** ret;
    return ret;
}*/

void calc_v_matrix(){
    float a_v = eye_x;
    float b_v = eye_y;
    float c_v = eye_z;

    float a_z = lookat_x - eye_x;
    float b_z = lookat_y - eye_y;
    float c_z = lookat_z - eye_z;

    float a_x = b_z;
    float b_x = -a_z;
    float c_x = 0;

    float r = sqrtf( (a_x*a_x) + (b_x * b_x) );
    float R = sqrtf( (a_x*a_x) + (b_x * b_x) + (c_x+c_x) );
    float h = r*sqrtf( (a_z*a_z) + (b_z * b_z) + (c_z * c_z) );

    float elements1[4][4] = { {1, 0, 0, 0},
			     {0, 1, 0, 0},
			     {0, 0, 1, 0},
			     {-a_v, -b_v, -c_v, 1} };

    float elements2[4][4] = { {a_x/r, -b_x/r, 0, 0},
			     {b_x/r, a_x/r, 0, 0},
			     {0, 0, 1, 0},
			     {0, 0, 0, 1} };

    float elements3[4][4] = { {r/R, 0, -c_x/R, 0},
			     {0, 1, 0, 0},
			     {c_x/R, 0, r/R, 0},
			     {0, 0, 0, 1} };

    float elements4[4][4] = { {1, 0, 0, 0},
			     {0, (c_z*R)/h, (b_z*a_x-a_z*b_x)/h, 0},
			     {0, (a_z*b_x-b_z*a_x)/h, c_z*R/h, 0},
			     {0, 0, 0, 1} };

    float elements5[4][4] = { {1, 0, 0, 0},
			     {0, 1, 0, 0},
			     {0, 0, 1, 0},
			     {0, 0, 0, 1} };

    Matrix* matrix = new Matrix(elements1);
    matrix = matrix->Multiply(new Matrix(elements2));
    matrix = matrix->Multiply(new Matrix(elements3));
    matrix = matrix->Multiply(new Matrix(elements4));
    matrix = matrix->Multiply(new Matrix(elements5));
    v_matrix = matrix;
}

void calc_p_matrix(){

    float elements[4][4] = { {viewplane, 0, 0, 0},
			     {0, viewplane, 0, 0},
			     {0, 0, (clipping_yon/(clipping_yon-clipping_hither)), 1},
			     {0, 0, ((-clipping_hither*clipping_yon)/(clipping_yon - clipping_hither)), 0}};
    Matrix* matrix = new Matrix(elements);
    p_matrix = matrix;
    
}

void calc_w_matrix(){
    float w_r = square_right-clipping_param;
    float w_l = square_left+clipping_param;
    float w_t = square_top-clipping_param;
    float w_b = square_bottom+clipping_param;

    float v_l, v_b; 
    v_l = v_b = -viewplane*tan(theta);
    float v_r, v_t;
    v_r = v_t = -v_l;


    float elements[4][4] = { {(w_r - w_l)/(v_r-v_l), 0, 0, 0},
			     {0, (w_t-w_b)/(v_t-v_b), 0, 0},
			     {0, 0, 1, 0},
			     {(w_l*v_r-v_l*w_r)/(v_r-v_l), (w_b*v_t-v_b*w_t)/(v_t-v_b), 0, 1}};
    Matrix* matrix = new Matrix(elements);
    w_matrix = matrix;
}

/***************************
 * Calc Full View Pipeline *
 * *************************/

Matrix* FullViewPipeLine(Matrix* input_coordinates ){
    //output is really just a vector
    Matrix* output = new Matrix();
    //printf("output rows and columns: %d, %d\n", output->rows, output->columns);
    output = input_coordinates->Multiply(v_matrix);
    //printf("output rows and columns: %d, %d\n", output->rows, output->columns);
    output = output->Multiply(p_matrix);
    //printf("output rows and columns: %d, %d\n", output->rows, output->columns);
    output = output->Multiply(w_matrix);
    //printf("output rows and columns: %d, %d\n", output->rows, output->columns);
    output = output->Homogenize(output);
    //printf("output rows and columns: %d, %d\n", output->rows, output->columns);
    //output->ToString();
    return output;
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

    calc_w_matrix();

    display();

}

/*call back function for theta user control*/
void clipping_callback(int ID) {

    calc_p_matrix();
    display();

}
/*********
 * MAIN *
 * ******/
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
	    true );

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
	    true );
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
	    GLUI_SPINNER_FLOAT,
	    &theta,
	    0,
	    theta_callback);
    /*speed_spinner->set_int_limits(0, 10, GLUI_LIMIT_CLAMP);*/

    /*******************/
    /*END USER CONTROLS*/
    /*******************/

    control_panel->set_main_gfx_window(main_window);
    GLUI_Master.set_glutIdleFunc(spinDisplay);
    //testMatrices();
    glutMainLoop();
    return EXIT_SUCCESS;

} 

/*
void testMatrices(){
    float matrixAElements[4][4] = { { 1, 1, 1, 1},
				    { 2, 2, 2, 2},
				    { 3, 3, 3, 3},
				    { 4, 4, 4, 4} };

    float matrixBElements[4][4] = { { 1, 2, 3, 4},
				    { 1, 2, 3, 4},
				    { 1, 2, 3, 4},
				    { 1, 2, 3, 4} };

    Matrix* A = new Matrix(matrixAElements);
    Matrix* B = new Matrix(matrixBElements);

    Matrix* result = A->Multiply(B);


    cout << result->ToString() << endl;

}
*/






