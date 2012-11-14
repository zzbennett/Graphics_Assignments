
#include "hw3.h"

void init() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(0.0, 0.0, 0.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(X, Y, Z, 0.0, 0.0, 0.0, 0.0,  1.0, 0.0);
}


void reshape(int w, int h) {
  glViewport(0, 0, w, h);

  float aspect = w*1.0/h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, aspect, 0.5, 200.0);
  glMatrixMode(GL_MODELVIEW);
  glutSetWindow(main_window);
  glutPostWindowRedisplay(main_window);  
}

/**********************************/
/*METHODS TO DRAW THE FERRIS WHEEL*/
/**********************************/

void ground(){
	glTranslatef(0, -WHEEL_RADIUS-5.0, 0);
    glRotatef(45.0, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluDisk(p, 0, 1000.0, 4, 4);
}


void base(){
    glTranslatef(0, -WHEEL_RADIUS-4.0, 0);
    glRotatef(45.0, 0.0, 1.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluDisk(p, 0, 20.0, 4, 4);
    glTranslatef(0, 0, -1.0);
    gluCylinder(p, 20.0, 20.0, 1.0, 4, 4);

}

void supports(){
    glPushMatrix();
    glTranslatef(0, 0, -2.0);
    glRotatef(10.0, 1.0, 0.0, WHEEL_RADIUS);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluCylinder(p, 0.5, 1.0, WHEEL_RADIUS+4.5, 4, 4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -2.0);
    glRotatef(-10.0, 1.0, 0.0, WHEEL_RADIUS);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluCylinder(p, 0.5, 1.0, WHEEL_RADIUS+4.5, 4, 4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 6.5);
    glRotatef(10.0, 1.0, 0.0, WHEEL_RADIUS);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluCylinder(p, 0.5, 1.0, WHEEL_RADIUS+4.5, 4, 4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 6.5);
    glRotatef(-10.0, 1.0, 0.0, WHEEL_RADIUS);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluCylinder(p, 0.5, 1.0, WHEEL_RADIUS+4.5, 4, 4);
    glPopMatrix();
}

void spokes(){
    //angle that each cart is away from each
    float increment = 360.0/NUM_CARTS;

    int i;

    glPushMatrix();
	glRotatef(spin_theta, 0.0, 0.0, 1.0);  //spin the ferris wheel
	for(i = 0; i<NUM_CARTS; i++){
	    glPushMatrix();
		glRotatef(increment*i, 0.0, 0.0, 1.0); //position spoke in wheel 
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(p, 0.10, 0.10, WHEEL_RADIUS, 16, 16);
	    glPopMatrix();
	    glPushMatrix();
		glRotatef(increment*i+180, 0.0, 0.0, 1.0); //position spoke in wheel 
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(p, 0.10, 0.10, WHEEL_RADIUS, 16, 16);
	    glPopMatrix();
	}
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0, 0, 5.0);
	glRotatef(spin_theta, 0.0, 0.0, 1.0);  //spin the ferris wheel
	for(i = 0; i<NUM_CARTS; i++){
	    glPushMatrix();
		glRotatef(increment*i, 0.0, 0.0, 1.0); //position spoke in wheel 
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(p, 0.10, 0.10, WHEEL_RADIUS, 16, 16);
	    glPopMatrix();
	    glPushMatrix();
		glRotatef(increment*i+180, 0.0, 0.0, 1.0); //position spoke in wheel 
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		gluCylinder(p, 0.10, 0.10, WHEEL_RADIUS, 16, 16);
	    glPopMatrix();
	}
    glPopMatrix();
}


void wheels(){

  glPushMatrix();
      glRotatef(spin_theta, 0.0, 0.0, 1.0);  //spin the ferris wheel

      //far side
      glutSolidTorus(0.5, WHEEL_RADIUS, 16, 16); //outer ring
      glutSolidTorus(0.25, WHEEL_RADIUS/2, 16, 16); //inner ring

      glPushMatrix();

	  glRotatef(180.0, 1.0, 0.0, 0.0); //make it point in the right direction
	  gluDisk(p, 0, WHEEL_RADIUS/8, NUM_CARTS, NUM_CARTS); //middle disk
	  gluCylinder(p, WHEEL_RADIUS/8, WHEEL_RADIUS/8, 0.5, NUM_CARTS, NUM_CARTS); //make middle disk 3D
	  glTranslatef(0.0, 0.0, .5); //make other side of middle disc
	  gluDisk(p, 0, WHEEL_RADIUS/8, NUM_CARTS, NUM_CARTS); //finish drawing middle disc

	  glPushMatrix();
	      gluCylinder(p, .5, .5, 2.0, NUM_CARTS, NUM_CARTS); //attachment to base
	      glTranslatef(0.0, 0.0, 2.0); 
	      gluDisk(p, 0, 0.5, NUM_CARTS, NUM_CARTS); //make the attachement to base a closed cylinder
	  glPopMatrix();

      glPopMatrix();

      //near side
      glPushMatrix();
      glRotatef(spin_theta, 0.0, 0.0, 1.0);  //spin the ferris wheel
	  glTranslatef(0.0, 0.0, 5.0); //drawing the other wheels now
	  glutSolidTorus(0.5, WHEEL_RADIUS, NUM_CARTS, NUM_CARTS); //outer ring
	  glutSolidTorus(0.25, WHEEL_RADIUS/2, NUM_CARTS, NUM_CARTS); //inner ring

	  gluDisk(p, 0, WHEEL_RADIUS/8, NUM_CARTS, NUM_CARTS); //middle disk
	  gluCylinder(p, WHEEL_RADIUS/8, WHEEL_RADIUS/8, 0.5, NUM_CARTS, NUM_CARTS); //make middle disk 3D
	  glPushMatrix();
	      glTranslatef(0.0, 0.0, .5); //make other side of middle disc
	      gluDisk(p, 0, WHEEL_RADIUS/8, NUM_CARTS, NUM_CARTS); //finish drawing middle disc
	  glPopMatrix();

	  gluCylinder(p, .5, .5, 2.0, NUM_CARTS, NUM_CARTS); //attachment to base
	  glPushMatrix();
	      glTranslatef(0.0, 0.0, 2.0);
	      gluDisk(p, 0, 0.5, NUM_CARTS, NUM_CARTS); //finish drawing attachment to base
	  glPopMatrix();
      glPopMatrix();
  glPopMatrix();
}

void carts(){

    float increment = 360.0/NUM_CARTS;
    
    glPushMatrix();
    glRotatef(spin_theta, 0.0, 0.0, 1.0);  //spin the ferris wheel
    for(int i = 0; i<NUM_CARTS; i++){

	//position cart correctly
	glPushMatrix();
	    glRotatef(increment*i, 0.0, 0.0, 1.0); //correct cart in correct position
	    glTranslatef(0, WHEEL_RADIUS, 0); //stick it at the edge of the wheels
	    glTranslatef(0, 0, 2.5); //put it in between the two wheels
	    glRotatef(-spin_theta-i*increment, 0.0, 0.0, 1.0); //keep cart upright

	    //umbrella
		changeMaterial(yellowPlasticMaterials);
	    glRotatef(-90.0, 1.0, 0.0, 0.0); //make it point up
	    gluCylinder(p, 2.0, 0.0, 2.0, 16, 16);

	    //bars
	    glPushMatrix();
			glTranslatef(0, 0, -2);  //down
			glTranslatef(0, -1.5, 0);  //right
			gluCylinder(p, 0.15, 0.15, 2.0, 4, 4);
	    glPopMatrix();

	    glPushMatrix();
			glTranslatef(0, 0, -2); //down
			glTranslatef(0, 1.5, 0); //left
			gluCylinder(p, 0.15, 0.15, 2.0, 4, 4);
	    glPopMatrix();

	    //box
		changeMaterial(bluePlasticMaterials);
		glPushMatrix();
			glTranslatef(0, 0, -4);
			glRotatef(45.0, 0.0, 0.0, 1.0);
			gluCylinder(p, 2.0, 2.0, 2.0, 4, 4);
			glRotatef(180.0, 0.0, 0.0, 1.0);
			gluDisk(p, 0.0, 2.0, 4, 4);
		glPopMatrix();


	    
	glPopMatrix();

    }

}

void lights(){
	
	float between_lights = (7*WHEEL_RADIUS/8) / NUM_CARTS;
    float increment = 360.0/NUM_CARTS;

    int i;
	int j;

    glPushMatrix();
	glRotatef(spin_theta, 0.0, 0.0, 1.0);  //spin the ferris wheel
	int int_spin_theta = (spin_theta * 100) / 100 + 1; //determines which lights go off when

	//are we in the flashing pattern or the growing pattern
	if((int_spin_theta % 100 == 0) && (int_spin_theta % 200 != 0) ){
		flashing = 0;
		changeMaterial(lightsOff);
	}
	else if(int_spin_theta % 200 == 0){
		flashing = 1;
	}

	
	if(flashing){//we're in the flashing pattern, set the lighting accordingly
		if((int_spin_theta % 5 == 0) && (int_spin_theta % 10 != 0) ){
			changeMaterial(lightsOn);
		}
		else if(int_spin_theta % 5 == 0){
			changeMaterial(lightsOff);
		}
	} 
	else{ //we're in the growing pattern
		if(int_spin_theta % 10 == 0){
			ring = (ring + 1) % NUM_CARTS;
		}
	}
	//far side
	for(i = 0; i<NUM_CARTS; i++){
	    glPushMatrix();
		glRotatef(increment*i, 0.0, 0.0, 1.0); //put lights on the correct spoke
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(0, 0, between_lights);
		for(j = 0; j<NUM_CARTS; j++){
			if(flashing){
				glTranslatef(0, 0, between_lights);
				gluSphere(p, .3, 8,8);		
			}
			else{
				if( ring == j ){
					changeMaterial(lightsOn);
				}
				else{
					changeMaterial(lightsOff);
				}
				glTranslatef(0, 0, between_lights);
				gluSphere(p, .3, 8,8);		
			}
		}
		
	    glPopMatrix();
	}
    glPopMatrix();

	//near side
    glPushMatrix();
	glTranslatef(0, 0, 5.0);
	glRotatef(spin_theta, 0.0, 0.0, 1.0);  //spin the ferris wheel
	for(i = 0; i<NUM_CARTS; i++){
	    glPushMatrix();
		glRotatef(increment*i, 0.0, 0.0, 1.0); //put lights on the correct spoke
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(0, 0, between_lights);
		for(j = 0; j<NUM_CARTS; j++){
			if(flashing){
				glTranslatef(0, 0, between_lights);
				gluSphere(p, .3, 8,8);		
			}
			else{
				if( ring == j ){
					changeMaterial(lightsOn);
				}
				else{
					changeMaterial(lightsOff);
				}
				glTranslatef(0, 0, between_lights);
				gluSphere(p, .3, 8,8);		
			}
		}
	    glPopMatrix();
	}
    glPopMatrix();

}


/******************/
/*DISPLAY FUNCTION*/
/******************/

void display() {
  glutSetWindow(main_window);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(X, Y, Z, 0.0, 0.0, 0.0, 0.0,  1.0, 0.0);

  glPushMatrix();

  /* ground */
  glPushMatrix();
  changeMaterial(greyPlasticMaterials);
  ground();
  glPopMatrix();


  /* base */
  glPushMatrix();
  changeMaterial(redPlasticMaterials);
  base();
  glPopMatrix();

  /* supports */
  changeMaterial(greenPlasticMaterials);
  glPushMatrix();
  supports();
  glPopMatrix();

  /* spokes */
  glPushMatrix();
  spokes();
  glPopMatrix();

  /* wheels */
  glPushMatrix();
  changeMaterial(redPlasticMaterials);
  wheels();
  glPopMatrix();

  /* carts */
  glPushMatrix();
  changeMaterial(yellowPlasticMaterials);
  carts();
  glPopMatrix();


  /* cool stuff? */
  glPushMatrix();
  changeMaterial(lightsOff);
  lights();
  glPopMatrix();


  glPopMatrix();
  glutSwapBuffers(); 
}

void eye_callback(int ID) {
  display();
}

void speed_callback(int ID) {
  display();
}

void spinDisplay() { /*This is the idle function*/
  spin_theta += 0.01*speed;
  display();
}

void changeMaterial(materialStruct newMaterial){
  currentMaterials = &newMaterial;
  glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(650, 650);
  glutInitWindowPosition(50, 50);
  main_window = glutCreateWindow("Amazing Ferris Wheel!");

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  /* HERE'S MY LIGHT */
  glEnable(GL_LIGHT0); 
  currentMaterials = &redPlasticMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);
  currentLighting = &whiteLighting;
  glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);

  p = gluNewQuadric();
  q = gluNewQuadric();
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  init();

  GLUI *control_panel = GLUI_Master.create_glui( "Controls",0, 50, 700 );

  new GLUI_Button(control_panel, "Quit", 0, (GLUI_Update_CB)exit);

  new GLUI_Column(control_panel, true);

   GLUI_Rollout *eye_rollout = control_panel->add_rollout("Camera Position", false );
  GLUI_Spinner *x_spin=control_panel->add_spinner_to_panel(eye_rollout, "X", GLUI_SPINNER_FLOAT, &X, 1, eye_callback);
  x_spin->set_float_limits(-100.0, 100.0, GLUI_LIMIT_CLAMP);
  GLUI_Spinner *y_spin=control_panel->add_spinner_to_panel(eye_rollout, "Y", GLUI_SPINNER_FLOAT, &Y, 2, eye_callback);
  y_spin->set_float_limits(-100.0, 100.0, GLUI_LIMIT_CLAMP);
  GLUI_Spinner *z_spin=control_panel->add_spinner_to_panel(eye_rollout, "Z", GLUI_SPINNER_FLOAT, &Z, 3, eye_callback);
  z_spin->set_float_limits(-300.0, 300.0, GLUI_LIMIT_CLAMP);

  new GLUI_Column(control_panel, true);
  GLUI_Rollout *speed_rollout = new GLUI_Rollout(control_panel, "Speed", false );

  GLUI_Spinner *speed_spinner= new GLUI_Spinner(speed_rollout, "Speed:", GLUI_SPINNER_INT, &speed, 0, speed_callback);
  speed_spinner->set_int_limits(0, 10, GLUI_LIMIT_CLAMP);

  control_panel->set_main_gfx_window(main_window); 
  GLUI_Master.set_glutIdleFunc(spinDisplay);

  glutMainLoop();
}
