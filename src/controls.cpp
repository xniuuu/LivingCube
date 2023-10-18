#include "controls.h"

double rotate_y, rotate_x, rotate_z, mouse_left_x, mouse_left_y = 0;

int key_switch = 0;
int scenario_switch = SELECT_SCENARIO;

void changeViewKey(unsigned char key, int x, int y){
  glEnable(GL_DEPTH_CLAMP);

  if(key == 'w')
    rotate_y += 0.1;

  else if(key == 's')
    rotate_y -= 0.1;

  else if(key == 'd')
    rotate_x += 0.1;

  else if (key == 'a')
    rotate_x -= 0.1;

  glutPostRedisplay();
}

void changeEmotionsKey(int key, int x, int y){
  glEnable(GL_DEPTH_CLAMP);

  if(key == GLUT_KEY_RIGHT)
    key_switch = (key_switch + 1) % 6;

  else if(key == GLUT_KEY_LEFT)
    key_switch = (key_switch - 1 + 6) % 6;

  else if(key == GLUT_KEY_UP)
    scenario_switch = (scenario_switch + 1) % 13;

  else if(key == GLUT_KEY_DOWN)
    scenario_switch = (scenario_switch - 1 + 6) % 6;

  glutPostRedisplay();
}

void MouseButton(int button, int state, int mousex, int mousey){

  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
     mouse_left_x  = mousex - glutGet( GLUT_WINDOW_WIDTH )/2;
     mouse_left_y = glutGet( GLUT_WINDOW_HEIGHT )/2 - mousey;
     mouse_left_x/=50;
     mouse_left_y/=50;
  }
  glutPostRedisplay();
}

void MouseMotion(int x, int y){

    mouse_left_x  = x- glutGet( GLUT_WINDOW_WIDTH )/2;
    mouse_left_y = glutGet( GLUT_WINDOW_HEIGHT )/2 - y;
    mouse_left_x/=50;
    mouse_left_y/=50;

    glutPostRedisplay();
}

void checkExternTransformations() {
  // Scale object via mouse
  if (ENABLE_MOUSE_SCALING) {
      glScalef(1.0+mouse_left_x, 1.0+mouse_left_y, 1.0+mouse_left_x);
  }
}
