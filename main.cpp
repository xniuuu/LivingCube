#include "main.h"

int main(int argc, char* argv[]){

  /*functions starting with 'Gl' are OpenGL functions;
    functions starting with 'glut' are GLUT functions;
    check reference pages for more detailed descriptions of these functions*/

  //Initialize GLUT and process user parameters
  glutInit(&argc,argv);

  //Request double buffered true color window with Z-buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800,600);
  //Set the window position
  glutInitWindowPosition(100,100);
  //Create window
  glutCreateWindow("Living Cube");

  //Enable Z-buffer depth test
  glEnable(GL_DEPTH_TEST);
  //get rid of the z-plane clipping
  glEnable(GL_DEPTH_CLAMP);

  glutDisplayFunc(renderScene);
  glutSpecialFunc(changeEmotionsKey);
  glutKeyboardFunc(changeViewKey);
  glutMouseFunc(MouseButton);
  glutMotionFunc(MouseMotion);

  glutMainLoop();

  return 0;
}
