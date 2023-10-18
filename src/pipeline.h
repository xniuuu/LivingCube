#ifndef PIPELINE_H
#define PIPELINE_H

#include "animations.h"
#include "controls.h"

/*this function prevents the cube to eypand or shrink, when changing the window size
  OpenGL functions: glMatrixMode(), glLoadIdentity(), glOrtho()
  OpenGL GLenum modes: GL_PROJECTION, GL_MODELVIEW
  GLUT functions: glutGet()
  GLUT window/screen enums: GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT */
void windowResize();

/*renders the cube by passing this function as a parameter to glutDisplayFunc()
  OpenGL functions: glutDisplayFunc()*/
void renderScene();

/*applies the emotion to the long_dis_walking() function */
void changeEmotions();


/*the following functions are different scenarios displaying the cuve moving along a given path;
  the view can be changed using the keys w, a, s, d;
  the emotion can be changed with the left and right arrow key*/

/*scenario 1-4: movements along a single curve, these should give an idea how the cube moves along a given path;
  for scenario 1 & 4: if STATIC_CUBE is 0 in config.h, the cube also bends its shape along the curve;
  the camera does not follow the cube */
void scenario1();
void scenario2();
void scenario3();
void scenario4();

/*scenario 5-10: movement along 4 curves, each scenario displays s different emotion;
  see (insert paper chapter) how the mapping to 4 curves works;
  the camera does not follow the cube */
void calmBoredom();
void happiness();
void excitement();
void sadness();
void anger();
void fear();

/*scenario 11 and 12: static emotion transitions (not changeable with keys) with 4 curves;
  the camera does not follow the cube */
void calmSad();
void excitedSadCalmAngry();

/*scenario 13: movement along 10 curves: the cube starts at a neutral emotion;
  more about how the different emotions are ordered, see (insert paper chapter);
  the camera does follow the cube */
void switchEmotions();

#endif
