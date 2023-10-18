#ifndef CONTROLS_H
#define CONTROLS_H

#include "opengl.h"
#include "../config.h"

/*angle to change the view*/
extern double rotate_y;
extern double rotate_x;

/*stores the position of the mouse;
the positions are not the coordinates of the mouse in the window! They have been modified, such that the cube does not scale absurdly*/
extern double mouse_left_x;
extern double mouse_left_y;

/*stores a value from 0 to 5, each refering to an emotion (cube) */
extern int key_switch;

/*stores values from 1 to 13, the initial value is equal to the value SELECT_SCENARIO from config.h*/
extern int scenario_switch;
/*Change OpenGLs state using keyboard inputs;
this function is passed as a parameter to glutSpecialFunc()
OpenGL functions: glutSpecialFunc()*/
void changeEmotionsKey(int key, int x, int y);

/*This function is passed as a parameter to glutKeyboardFunc()
OpenGL functions: glutKeyboardFunc()*/
void changeViewKey(unsigned char key, int x, int y);

/*This functions is passed as a parameter to glutMouseFunc()
GLUT functions: glutMouseFunc()*/
void MouseButton(int button, int state, int mousex, int mousey);

/*Scales the cube using mouse left click and dragging;
this function is passed as a parameter to glutMotionFunc()
GLUT functions: glutMotionFunc()*/
void MouseMotion(int x, int y);

/*Function that enables/disables scaling with mouse*/
void checkExternTransformations();


#endif
