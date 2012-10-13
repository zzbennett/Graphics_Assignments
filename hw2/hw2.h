
#include<stdio.h>
#include<GL/glut.h>
#include<GL/glui.h>
#include<string>
#include<math.h>
#include<iostream>
#include"Matrix.h"

#define true 1
#define false 0
#define INITIAL_WIDTH 500
#define INITIAL_HEIGHT 500
#define XSCALE 10.0
#define YSCALE 10.0
#define PI 3.1415926535
#define SQUARE_OFFSET 0.1

using namespace std;

/******************/
/*GLOBAL VARIABLES*/
/******************/

int main_window;

int global_w = INITIAL_WIDTH;
int global_h = INITIAL_HEIGHT;

float cube_size = 10.0;

GLfloat vertices[8][3] = {   {0,0,0}, /*0*/
			    {0,cube_size, 0}, /*1*/
			    {cube_size, 0, 0}, /*2*/
			    {cube_size, cube_size, 0}, /*3*/
			    {0, 0, cube_size}, /*4*/
			    {0, cube_size, cube_size}, /*5*/
			    {cube_size, 0, cube_size}, /*6*/
			    {cube_size, cube_size, cube_size} /*7*/ };
			    
float eye_x = 18.0;
float eye_y = 20.0;
float eye_z = 15.0;


float lookat_x = 0;
float lookat_y = 0;
float lookat_z = 0;

float clipping_param = 0;
float clipping_yon = 15;
float clipping_hither = 5;
float viewplane = 10;

GLfloat theta = 40;

int square_top;
int square_right; 

Matrix* v_matrix;
Matrix* p_matrix;
Matrix* w_matrix;

void calc_v_matrix();
void calc_p_matrix();
void calc_w_matrix();

float up_vector[3] = {0, 0, 1};

Matrix* FullViewPipeLine(Matrix* input_coordinates);
void draw_line(float v_1[3], float v_2[3]);

