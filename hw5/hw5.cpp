/*     TextureExamples/SplineFileTextureSpots.cpp  */ 
/*
 *  This final example shows the vase from SplineExamples/closedSurface.cpp.  
 *  This time we load a texture map from an image file whose
 *  dimensions are not powers of 2; we resize the image into
 *  a texture map and use it to texture the surface.  The image
 *  file is "spots.ppm".
 */

#include "hw5.h"

void skipToEndOfLine(FILE *fd) {
  char c;
  do {
    fscanf(fd, "%c", &c);
  } while (c != '\n');
}


void makeTextureMaps() {
  FILE *fd;
  char string[100];
  char c;
  int max;
  float s;
  unsigned int red, green, blue;
  GLubyte br, bg, bb;
  GLfloat *buffer;

  /*******CLOUD TEXTURE***********/
  /* first read the file into a buffer */
  fd = fopen("clouds.ppm", "r");
  fscanf( fd, "%s", string);
  if (string[0] !=  'P' || string[1] != '6'){
    printf( "sorry; not a ppm file\n" );
    exit(0);
  }
  skipToEndOfLine(fd);
  fscanf( fd, "%c", &c); /* reads first char of next line */
  while (c == '#') {
    skipToEndOfLine(fd);
    fscanf(fd, "%c", &c); /* reads first char of next line */
  }
  ungetc(c, fd);
  fscanf( fd, "%u %u %u", &m, &n, &max);
  skipToEndOfLine(fd);
  printf( "sizes %d x %d\n", n, m);
  buffer = (GLfloat *)malloc(sizeof(GLfloat)*n*m*3);

  for (int i = 0; i < n; i++ ) 
    for (int j = 0; j < m; j++){
      fread(&br, 1, 1, fd);
      fread(&bg, 1, 1, fd);
      fread(&bb, 1, 1, fd);
      red = (int)br;
      green = (int)bg;
      blue =(int)bb;
    buffer[3*i*m + 3*j] = red/255.0;
    buffer[3*i*m + 3*j+1] = green/255.0;
    buffer[3*i*m + 3*j+2] = blue/255.0;
  }
  /* now make the actual texture map, which has dimensions that */
  /* are powers of 2 */
  textureMapCloud = (GLfloat *)malloc(sizeof(GLfloat)*1024*2048*3);
  gluScaleImage(GL_RGB, m, n, GL_FLOAT, buffer, 1024, 2048, GL_FLOAT, textureMapCloud); 
  free(buffer);

  /*******AIRPLANE TEXTURE***********/
  fd = fopen("polka_dots.ppm", "r");
  fscanf( fd, "%s", string);
  if (string[0] !=  'P' || string[1] != '6'){
    printf( "sorry; not a ppm file\n" );
    exit(0);
  }
  skipToEndOfLine(fd);
  fscanf( fd, "%c", &c); /* reads first char of next line */
  while (c == '#') {
    skipToEndOfLine(fd);
    fscanf(fd, "%c", &c); /* reads first char of next line */
  }
  ungetc(c, fd);
  fscanf( fd, "%u %u %u", &m, &n, &max);
  skipToEndOfLine(fd);
  printf( "sizes %d x %d\n", n, m);
  buffer = (GLfloat *)malloc(sizeof(GLfloat)*n*m*3);

  for (int i = 0; i < n; i++ ) 
    for (int j = 0; j < m; j++){
      fread(&br, 1, 1, fd);
      fread(&bg, 1, 1, fd);
      fread(&bb, 1, 1, fd);
      red = (int)br;
      green = (int)bg;
      blue =(int)bb;
    buffer[3*i*m + 3*j] = red/255.0;
    buffer[3*i*m + 3*j+1] = green/255.0;
    buffer[3*i*m + 3*j+2] = blue/255.0;
  }
  /* now make the actual texture map, which has dimensions that */
  /* are powers of 2 */
  textureMapAirplane = (GLfloat *)malloc(sizeof(GLfloat)*256*256*3);
  gluScaleImage(GL_RGB, m, n, GL_FLOAT, buffer, 256, 256, GL_FLOAT, textureMapAirplane); 
  free(buffer);
}

void makeTextures(){
    /** CLOUD **/
    glGenTextures(1, &cloudTexID);
    //glBindTexture(GL_TEXTURE_2D, cloudTexID);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 2048, 0, GL_RGB, GL_FLOAT, textureMapCloud);

    /** AIRPLANE **/
    glGenTextures(2, &airplaneTexID);
    //glBindTexture(GL_TEXTURE_2D, airplaneTexID);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_FLOAT, textureMapAirplane);
}

void switchTextures(int texture) {
    switch(texture){
	case CLOUD:
	    //glDisable(GL_TEXTURE_2D);
	    glEnable(GL_TEXTURE_2D);
	    //glGenTextures(1, &cloudTexID);
	    glBindTexture(GL_TEXTURE_2D, cloudTexID);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 2048, 0, GL_RGB, GL_FLOAT, textureMapCloud);
	    break;
	case AIRPLANE:
	    //glDisable(GL_TEXTURE_2D);
	    glEnable(GL_TEXTURE_2D);
	    //glGenTextures(2, &airplaneTexID);
	    glBindTexture(GL_TEXTURE_2D, airplaneTexID);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_FLOAT, textureMapAirplane);
	    break;
    }

}


void buildObject(float radius, float height, GLfloat data[13][3], int object_num) {
  int i;

  //GLfloat object[13][3];

  switch(object_num){
      case BODY:
	  for (i = 0; i < 13; i++ ) {
	      data[i][0] = body[i][0]*radius;
	      data[i][1] = body[i][1]*radius;
	      data[i][2] = height;
	  }
	  break;
      case WING:
	  for (i = 0; i < 13; i++ ) {
	      data[i][0] = wing[i][0]*radius;
	      data[i][1] = wing[i][1]*radius;
	      data[i][2] = height;
	  }
	  break;
      case DORSAL:
	  for (i = 0; i < 13; i++ ) {
	      data[i][0] = dorsal[i][0]*radius;
	      data[i][1] = dorsal[i][1]*radius;
	      data[i][2] = height;
	  }
	  break;
      case SIDEDORSAL:
	  for (i = 0; i < 13; i++ ) {
	      data[i][0] = side_dorsal[i][0]*radius;
	      data[i][1] = side_dorsal[i][1]*radius;
	      data[i][2] = height;
	  }
	  break;
  }
}

void buildSurfaceOfRotation( ) {
    /**** BODY ****/
  buildObject( 0.0, 14.0, bodyControlPoints[0], BODY );
  buildObject( 0.5, 13.5, bodyControlPoints[1], BODY);
  buildObject( 1.15, 13.0, bodyControlPoints[2], BODY );
  buildObject( 1.15, 9.0, bodyControlPoints[3], BODY );
  buildObject( 1.15, 8.0, bodyControlPoints[4], BODY );
  buildObject( 1.15, 7.0, bodyControlPoints[5], BODY );
  buildObject( 1.15, 6.0, bodyControlPoints[6], BODY );
  buildObject( 1.15, 2.0, bodyControlPoints[7], BODY );
  buildObject( 0.5, 1.5, bodyControlPoints[8], BODY );
  buildObject( 0.0, 1.0, bodyControlPoints[9], BODY );

    /**** WING ****/
  buildObject( 0.0, 9.5, wingControlPoints[0], WING );
  buildObject( 0.25, 9.0, wingControlPoints[1], WING);
  buildObject( 0.75, 8.5, wingControlPoints[2], WING );
  buildObject( 0.75, 8.0, wingControlPoints[3], WING );
  buildObject( 0.75, 7.5, wingControlPoints[4], WING );
  buildObject( 0.75, 7.0, wingControlPoints[5], WING );
  buildObject( 0.75, 6.5, wingControlPoints[6], WING );
  buildObject( 0.5, 6.0, wingControlPoints[7], WING );
  buildObject( 0.25, 5.5, wingControlPoints[8], WING );
  buildObject( 0.0, 5.0, wingControlPoints[9], WING );

  	/**** DORSAL ****/
  buildObject( 0.0, 3.5,  dorsalControlPoints[0], DORSAL );
  buildObject( 0.25, 3.0, dorsalControlPoints[1], DORSAL );
  buildObject( 0.5, 2.5, dorsalControlPoints[2], DORSAL );
  buildObject( 0.5, 2.0, dorsalControlPoints[3], DORSAL );
  buildObject( 0.5, 1.5, dorsalControlPoints[4], DORSAL );
  buildObject( 0.5, 1.0, dorsalControlPoints[5], DORSAL );
  buildObject( 0.25, 0.5, dorsalControlPoints[6], DORSAL );
  buildObject( 0.0, 0.0,  dorsalControlPoints[7], DORSAL );
  
  	/**** SIDE DORSALS ****/
  buildObject( 0.0, 2.0,  sideDorsalControlPoints[0], SIDEDORSAL );
  buildObject( 0.25, 1.75, sideDorsalControlPoints[1], SIDEDORSAL );
  buildObject( 0.5, 1.5,  sideDorsalControlPoints[2], SIDEDORSAL );
  buildObject( 0.5, 1.25,  sideDorsalControlPoints[3], SIDEDORSAL );
  buildObject( 0.5, 1.0,  sideDorsalControlPoints[4], SIDEDORSAL );
  buildObject( 0.5, 0.75,  sideDorsalControlPoints[5], SIDEDORSAL );
  buildObject( 0.25, 0.25, sideDorsalControlPoints[6], SIDEDORSAL );
  buildObject( 0.0, 0.0,  sideDorsalControlPoints[7], SIDEDORSAL );
}

void display(void) {
  int row, col;
  GLfloat patch[4][4][3];
  float texel[2][2][2] = { {{0.0, 0.0}, {1.0, 0.0}}, {{0.0, 1.0}, {1.0, 1.0}}};

  glEnable(GL_MAP2_TEXTURE_COORD_2);
  glutSetWindow(main_window);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(X, Y, Z, 0.0, 0.0, 5.0, 0.0,  0.0, 1.0);
  buildSurfaceOfRotation();

  
  /** AIRPLANE STUFF **/
  glPushMatrix();
  glTranslatef(0.0, 0.0, -5.0);
  
  /**** BODY ****/
  glPushMatrix();
  //glRotatef(theta, 0.0, 0.0, 1.0);
  glRotatef(90, 1.0, 0.0, 0.0);
  for (row=0; row < 4; row++) {
    for (col = 0; col < 4; col++) {
      glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 39, 4, &bodyControlPoints[3*row][3*col][0]);
      //glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2, &texel[0][0][0]);
      glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
      glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    } 
  }
  glPopMatrix();

  /**** LEFT WING ****/
  glPushMatrix();
  //glRotatef(theta, 0.0, 0.0, 1.0);
  glRotatef(90, 1.0, 0.0, 0.0);
  glRotatef(180, 0.0, 0.0, 1.0);
  for (row=0; row < 4; row++) {
    for (col = 0; col < 4; col++) {
      glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 39, 4, &wingControlPoints[3*row][3*col][0]);
      //glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2, &texel[0][0][0]);
      glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
      glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    } 
  }
  glPopMatrix();


  /**** RIGHT WING ****/
  glPushMatrix();
  //glRotatef(theta, 0.0, 0.0, 1.0);
  glRotatef(90, 1.0, 0.0, 0.0);
  //glRotatef(180, 0.0, 0.0, 1.0);
  for (row=0; row < 4; row++) {
    for (col = 0; col < 4; col++) {
      glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 39, 4, &wingControlPoints[3*row][3*col][0]);
      //glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2, &texel[0][0][0]);
      glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
      glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    } 
  }
  glPopMatrix();

  /*
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, airplaneTexID);
  */
  switchTextures(AIRPLANE);

  /* LEFT DECAL */
  glPushMatrix();
  glTranslatef(8.0, 0.0, 0.0);
  glTranslatef(0.0, -6.5, 0.0);
  glTranslatef(0.0, 0.0, 0.05);
  glRotatef(6.35, 1.0, 1.0, 0.0);
  glRotatef(90, 0.0, 0.0, 1.0);
  glRotatef(25, 0.0, 1.0, 0.0);
  glBegin(GL_POLYGON);
	  glTexCoord2f(0,0);
  glVertex3f(0, 0, 0);
	  glTexCoord2f(1,0);
  glVertex3f(0, 7, 0);
	  glTexCoord2f(1,1);
  glVertex3f(2, 7, 0);
	  glTexCoord2f(0,1);
  glVertex3f(0.15, 0, 0);
  glEnd();
  glPopMatrix();

  /* RIGHT DECAL */
  glPushMatrix();
  glTranslatef(-8.0, 0.0, 0.0);
  glTranslatef(0.0, -6.5, 0.0);
  glTranslatef(0.0, 0.0, 0.20);
  glRotatef(180, 0.0, 0.0, 1.0);
  glRotatef(6.35, 1.0, 1.0, 0.0);
  glRotatef(90, 0.0, 0.0, 1.0);
  glRotatef(-25, 0.0, 1.0, 0.0);
  glBegin(GL_POLYGON);
	  glTexCoord2f(0,0);
  glVertex3f(0, 0, 0);
	  glTexCoord2f(1,0);
  glVertex3f(0, 7, 0);
	  glTexCoord2f(1,1);
  glVertex3f(-2, 7, 0);
	  glTexCoord2f(0,1);
  glVertex3f(-0.15, 0, 0);
  glEnd();
  glPopMatrix();


  /**** DORSAL ****/
  glPushMatrix();
  //glRotatef(theta, 0.0, 0.0, 1.0);
  glRotatef(90, 1.0, 0.0, 0.0);
  glRotatef(-90, 0.0, 0.0, 1.0);
  glTranslatef(-0.5, 0.0, 1.5);
  for (row=0; row < 4; row++) {
    for (col = 0; col < 4; col++) {
      glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 39, 4, &dorsalControlPoints[3*row][3*col][0]);
      glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2, &texel[0][0][0]);
      glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
      glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    } 
  }
  glPopMatrix();

  /**** LEFT DORSAL ****/
  glPushMatrix();
  //glRotatef(theta, 0.0, 0.0, 1.0);
  glRotatef(90, 1.0, 0.0, 0.0);
  glRotatef(180, 0.0, 0.0, 1.0);
  glTranslatef(-0.5, 0.0, 1.5);
  for (row=0; row < 4; row++) {
    for (col = 0; col < 4; col++) {
      glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 39, 4, &sideDorsalControlPoints[3*row][3*col][0]);
      glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2, &texel[0][0][0]);
      glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
      glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    } 
  }
  glPopMatrix();

  /**** RIGHT DORSAL ****/
  glPushMatrix();
  //glRotatef(theta, 0.0, 0.0, 1.0);
  glRotatef(90, 1.0, 0.0, 0.0);
  //glRotatef(, 0.0, 0.0, 1.0);
  glTranslatef(-0.5, 0.0, 1.5);
  for (row=0; row < 4; row++) {
    for (col = 0; col < 4; col++) {
      glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 39, 4, &sideDorsalControlPoints[3*row][3*col][0]);
      glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2, &texel[0][0][0]);
      glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
      glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    } 
  }
  glPopMatrix();

  glPopMatrix(); /* end airplane stuff */

  switchTextures(CLOUD);

  /**** BACKGROUND ****/
  glPushMatrix();
  //glRotatef(180, 0.0, 1.0, 0.0);
  //glRotatef(45.0, 0.0, 1.0, 0.0);
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  glTranslatef(0.0, 0.0, -50);
  //glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2, &texel[0][0][0]);
      glBegin(GL_POLYGON);
	  glTexCoord2f(0,0);
	  glVertex3f(-100, -50, 0);
	  glTexCoord2f(1,0);
	  glVertex3f(100, -50, 0);
	  glTexCoord2f(1,1);
	  glVertex3f(100, 50, 0);
	  glTexCoord2f(0,1);
	  glVertex3f(-100, 50, 0);
	  glEnd();
  //gluDisk(p, 0, 10.0, 4, 4);
  glPopMatrix();
  

  glutSwapBuffers();
  glDisable(GL_TEXTURE_2D);
}

void myReshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective( 45.0, w*1.0/h, 0.5, 200);
  glMatrixMode(GL_MODELVIEW);
  glutSetWindow(main_window);
  glutPostWindowRedisplay(main_window);  
}

void myInit() {
  GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat position[] = {30.0, 15.0, 10.0, 1.0};
  GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat mat_diffuse[] = {0.8, 0.8, 0.8, 1.0};
  GLfloat mat_specular[] = {0.4, 0.4, 0.4, 1.0};
  GLfloat mat_shininess[] = {50.0};

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(20.0, 5.0, 10.0, 0.0, 2.0, 5.0, 0.0,  0.0, 1.0);

  makeTextureMaps();
  makeTextures();

 //glEnable(GL_TEXTURE_2D);
  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_MAP2_VERTEX_3);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT0, GL_POSITION, position);

  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

}

void spin() {
  theta += 0.1;
  glutPostRedisplay();

}

void eye_callback(int ID) {
  display();
}

int main(int argc, char *argv[]) {
  int i, j, k, m, n;
  p = gluNewQuadric();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  main_window = glutCreateWindow("Airplane!");
  glutReshapeFunc(myReshape); 
  glutDisplayFunc(display);
  myInit();

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

  control_panel->set_main_gfx_window(main_window); 
  GLUI_Master.set_glutIdleFunc(spin);

  glutMainLoop();
}










