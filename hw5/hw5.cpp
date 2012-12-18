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


void makeTextureMap() {
  FILE *fd;
  char string[100];
  char c;
  int max;
  float s;
  unsigned int red, green, blue;
  GLubyte br, bg, bb;
  GLfloat *buffer;

  /* first read the file into a buffer */
  fd = fopen("spots.ppm", "r");
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
  textureMap = (GLfloat *)malloc(sizeof(GLfloat)*256*256*3);
  gluScaleImage(GL_RGB, m, n, GL_FLOAT, buffer, 256, 256, GL_FLOAT, textureMap); 
}
void makeTextures() {
  glGenTextures(1, &texID);

  glBindTexture(GL_TEXTURE_2D, texID);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_FLOAT, textureMap);
}


void buildCircle(float radius, float height, GLfloat data[13][3]) {
  int i;

  for (i = 0; i < 13; i++ ) {
    data[i][0] = circle[i][0]*radius;
    data[i][1] = circle[i][1]*radius;
    data[i][2] = height;
  }
}

void buildSurfaceOfRotation( ) {
  buildCircle( 1.0, 8.0, controlPoints[0] );
  buildCircle( 1.0, 7.0, controlPoints[1] );
  buildCircle( 1.5, 6.0, controlPoints[2] );
  buildCircle( 1.5, 5.0, controlPoints[3] );
  buildCircle( 1.5, 4.0, controlPoints[4] );
  buildCircle( 2.5, 3.0, controlPoints[5] );
  buildCircle( 2.5, 2.0, controlPoints[6] );
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

  glBindTexture(GL_TEXTURE_2D, texID);
  glPushMatrix();
  glRotatef(theta, 0.0, 0.0, 1.0);
  for (row=0; row < 2; row++) {
    for (col = 0; col < 4; col++) {
      glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 39, 4, &controlPoints[3*row][3*col][0]);
      glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2, &texel[0][0][0]);
      glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
      glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    } 
  }
  glPopMatrix();
  
  glutSwapBuffers();
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
  GLfloat mat_ambient[] = {0.1, 0.1, 0.1, 1.0};
  GLfloat mat_diffuse[] = {0.8, 0.8, 0.8, 1.0};
  GLfloat mat_specular[] = {0.4, 0.4, 0.4, 1.0};
  GLfloat mat_shininess[] = {50.0};

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(20.0, 5.0, 10.0, 0.0, 2.0, 5.0, 0.0,  0.0, 1.0);

  makeTextureMap();
  makeTextures();

 glEnable(GL_TEXTURE_2D);
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

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  main_window = glutCreateWindow("Breakfast of champions");
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










