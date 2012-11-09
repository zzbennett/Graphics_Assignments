/* Homework 1
 * Liz Bennett
 * Due Sept. 17, 11:59pm
 *
 * Creates a spinning wheel with variegated grey colors
 * and user control box
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


int main_window;

GLfloat x=5.0, y=5.0;
int color = 1;
GLfloat side = 3.0;
GLfloat theta = 0.0;

int num_sides = 8;
int speed = 5; /*scale from 0 - 10 */
int sides_id = 2;
float LOWER_COLOR_THRESHOLD = .10;
float UPPER_COLOR_THRESHOLD = .90;


void setupViewport(int w, int h) {
  glViewport(0, 0, w, h); 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(0.0, XSCALE*w/INITIAL_WIDTH, 0.0, h*YSCALE/INITIAL_HEIGHT );
}

void init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glColor3f(1.0, 1.0, 0.0);  /* yellow */
  setupViewport(INITIAL_WIDTH, INITIAL_HEIGHT);
}

void myReshape(int w, int h) {
  setupViewport(w, h);
  glutPostWindowRedisplay(main_window);  
}

GLfloat radians(float alpha) {
  return alpha*PI/180.0;
}

void display(){
  int i;
  float alpha;
  
  glutSetWindow(main_window);
  glClear(GL_COLOR_BUFFER_BIT);

  /*range of grey spectrum*/
  float range = UPPER_COLOR_THRESHOLD - LOWER_COLOR_THRESHOLD;
  float c;
  float slope;

  for( i = 0; i<num_sides; i++){
      /*set pen color*/
      if( i<num_sides/2 ) {
	  slope = ( range/((num_sides/2.0) * (num_sides/2.0)) );
	  c = LOWER_COLOR_THRESHOLD + slope * (i*i);
	  glColor3f(c,c,c);
      }
      else{
	  slope = ( range/((num_sides/2.0) * (num_sides/2.0)) );
	  c = LOWER_COLOR_THRESHOLD + slope * ((-num_sides+i)*(-num_sides+i));
	  glColor3f(c,c,c);
      }
      /***************/
      

      /*draw polygon*/
      glBegin(GL_POLYGON);
	  glVertex2f(x, y);
	  glVertex2f(x+side*cos(radians(theta+i*(360.00/num_sides))), y+side*sin(radians(theta+i*(360.00/num_sides))));
	  glVertex2f(x+side*cos(radians(theta+(i+1)*(360.00/num_sides))), y+side*sin(radians(theta+(i+1)*(360.00/num_sides))));
	  glEnd();
  }
	/*************/

  glutSwapBuffers();
}

void sides_callback(int ID){

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
}


void speed_callback(int ID) {

  display();

}

void spinDisplay() { /*This is the idle function*/
  theta += 0.01*speed;
  display();
}

int main(int argc, char **argv) {
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(INITIAL_WIDTH, INITIAL_HEIGHT);
  glutInitWindowPosition(50, 50);
  main_window = glutCreateWindow( "Magic Spinny Grey Wheel" );

  init();
  glutDisplayFunc(display);
  glutReshapeFunc(myReshape);
  
  GLUI *control_panel = GLUI_Master.create_glui( "Controls");
  new GLUI_StaticText( control_panel, "Magic Controls" );
  new GLUI_Separator(control_panel);

  /*set color threshold */
  GLUI_Rollout *color_rollout = new GLUI_Rollout(control_panel, "Color Threshold", false );

  /*upper threshold*/
  GLUI_Spinner *ucolor_spinner= new GLUI_Spinner(color_rollout, "Upper Threshold:", GLUI_SPINNER_FLOAT, &UPPER_COLOR_THRESHOLD, 0, speed_callback);
  ucolor_spinner->set_float_limits(LOWER_COLOR_THRESHOLD, 1.0, GLUI_LIMIT_CLAMP);
  /*lower threshold*/
  GLUI_Spinner *lcolor_spinner= new GLUI_Spinner(color_rollout, "Lower Threshold:", GLUI_SPINNER_FLOAT, &LOWER_COLOR_THRESHOLD, 0, speed_callback);
  lcolor_spinner->set_float_limits(0.0, UPPER_COLOR_THRESHOLD, GLUI_LIMIT_CLAMP);
  
  new GLUI_Separator(control_panel);
  new GLUI_Button(control_panel, "Quit", 0, (GLUI_Update_CB)exit);



  new GLUI_Column(control_panel, true);

  GLUI_Rollout *speed_rollout = new GLUI_Rollout(control_panel, "Speed", false );

  GLUI_Spinner *speed_spinner= new GLUI_Spinner(speed_rollout, "Speed:", GLUI_SPINNER_INT, &speed, 0, speed_callback);
  speed_spinner->set_int_limits(0, 10, GLUI_LIMIT_CLAMP);

  /*SPEED RADIO BUTTONS*/

  /*SPINNERS*/
  /*GLUI_Spinner *xpos= new GLUI_Spinner(box_rollout, "X", GLUI_SPINNER_FLOAT, &x, 0, position_callback);
  xpos->set_float_limits(0.0, 10.0, GLUI_LIMIT_CLAMP);
  GLUI_Spinner *ypos= new GLUI_Spinner(box_rollout, "Y", GLUI_SPINNER_FLOAT, &y, 0, position_callback);
  ypos->set_float_limits(0.0, 10.0, GLUI_LIMIT_CLAMP);*/
  new GLUI_Separator(speed_rollout);
  GLUI_Rollout *sides_rollout = new GLUI_Rollout(control_panel, "Sides", false );

  GLUI_RadioGroup *group1 = new GLUI_RadioGroup(sides_rollout, &sides_id, 3, sides_callback);
  new GLUI_RadioButton(group1, "8" );
  new GLUI_RadioButton(group1, "16" );
  new GLUI_RadioButton(group1, "32" );
  new GLUI_RadioButton(group1, "64" );
  new GLUI_RadioButton(group1, "128" );
  group1->set_int_val(0); /*defaul set to 8*/

  /*TEXT BOX*/
  /*new GLUI_StaticText(box_rollout, "Color:" );*/


  control_panel->set_main_gfx_window(main_window);
  GLUI_Master.set_glutIdleFunc(spinDisplay);
  glutMainLoop();

  return EXIT_SUCCESS;

} 
