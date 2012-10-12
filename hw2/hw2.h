using namespace std;

#include<stdio.h>
#include<GL/glut.h>
#include<GL/glui.h>
#include<math.h>
#include"Matrix.h"

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

GLfloat vertices[][3] = {   {0,0,0}, /*0*/
			    {0,cube_size, 0}, /*1*/
			    {cube_size, 0, 0}, /*2*/
			    {cube_size, cube_size, 0}, /*3*/
			    {0, 0, cube_size}, /*4*/
			    {0, cube_size, cube_size}, /*5*/
			    {cube_size, 0, cube_size}, /*6*/
			    {cube_size, cube_size, cube_size} /*7*/ };
			    
float eye_x = 50.0;
float eye_y = 26.375;
float eye_z = 23.41;


float lookat_x = 0;
float lookat_y = 0;
float lookat_z = 0;

float clipping_param = 0;
float clipping_yon = 15;
float clipping_hither = 5;

GLfloat theta;

int square_top;
int square_right; 

/*int** v_matrix;*/
int** p_matrix;
int** w_matrix;

Matrix* v_matrix;

void calc_v_matrix();
void calc_p_matrix();
void calc_w_matrix();


int up_vector[3] = {0, 0, 1};
