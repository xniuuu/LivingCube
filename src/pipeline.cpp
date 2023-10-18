#include "pipeline.h"

void windowResize(){

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double w = glutGet( GLUT_WINDOW_WIDTH )/100;
  double h = glutGet( GLUT_WINDOW_HEIGHT )/100;
  glOrtho( -w, w, -h, h, 10, -10);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void renderScene(){

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  windowResize();

  glm::vec3 cubePos = glm::vec3((float)qb.path_point.x, (float)qb.path_point.y, (float)qb.path_point.z);
  glm::vec3 camPos = cubePos + glm::vec3(0.25f + rotate_x, 0.20f + rotate_y, -0.5f);

  if(CAMERA_FOLLOW && SELECT_SCENARIO > 4){
    gluLookAt(cubePos.x, cubePos.y, cubePos.z, camPos.x, camPos.y, camPos.z, 0.0, 1.0, 0.0);
  }
  else {
    gluLookAt(0, 0, 0, rotate_x, rotate_y, -0.5f, 0.0, 1.0, 0.0);
  }

  glPushMatrix();

  if (ENABLE_CONTROLS) {
    checkExternTransformations();
  }

  switch (scenario_switch) {
      case  0: scenario1();            break;
      case  1: scenario2();            break;
      case  2: scenario3();            break;
      case  3: scenario4();            break;
      case  4: calmBoredom();         break;
      case  5: happiness();            break;
      case  6: excitement();           break;
      case  7: sadness();              break;
      case  8: anger();                break;
      case  9: fear();                 break;
      case 10: calmSad();             break;
      case 11: excitedSadCalmAngry(); break;
      case 12: switchEmotions();   break;
      default: switchEmotions();   break;
  }
  if(!ENABLE_CUBE_MOVEMENT && !ENABLE_MOUSE_SCALING){
    idleBreathing();
  }

  qb.drawCube();

  glPopMatrix();
  glutSwapBuffers();
  glutPostRedisplay();
}

void changeEmotions(){

  switch(key_switch){
    case 0: //calm or bored
      if(tilt_stop)
        tiltBack();
      squash(0.2, 0.005);
      if(squash_stop)
        stretch(0.2, 0.01);
      if(stretch_reverse && forward){
        rotation(0.3, 0.01, 1);
        moveCubeForwardCurve();
      }
      break;
    case 1: //happy
      if(tilt_stop)
        tiltBack();
      squash(0.3, 0.03);
      if(squash_stop)
        stretch(0.3, 0.06);
      if(stretch_reverse && forward){
        moveCubeForwardCurve();
      }
      break;
    case 2: //excited
      if(tilt_stop)
        tiltBack();
      squash(0.3, 0.02);
      if(squash_stop)
        stretch(0.5, 0.05);
      if(stretch_reverse && forward){
        spin(12.56, 0.15);
        moveCubeForwardCurve();
      }
      break;
    case 3: //sad
      tilt(0.8, 0.04, 0);
      squash(0.2, 0.005);
      if(squash_stop)
        stretch(0.2, 0.01);
      if(stretch_reverse && forward){
        rotation(0.3, 0.01, 1);
        moveCubeForwardCurve();
      }
      break;
    case 4: //angry
      if(tilt_stop)
        tiltBack();
      shake(0.1);
      squash(0.5, 0.03);
      if(squash_stop)
        stretch(0.5, 0.05);
      if(stretch_reverse && forward){
        rotation(0.3, 0.01, 1);
        moveCubeForwardCurve();
      }
      break;
    case 5: //fear
      tilt(0.5, 0.01, 1);
      shake(0.03);
      squash(0.2, 0.002);
      if(squash_stop)
        stretch(0.2, 0.004);
      if(stretch_reverse && forward){
        rotation(0.3, 0.01, 1);
        moveCubeForwardCurve();
      }
      break;
  }
}

void scenario1(){
  qb.cubeAt(curve1, t);
  if (ENABLE_CUBE_MOVEMENT) {
    if(forward){
      squash(0.5, 0.02);
      if(squash_stop)
        stretch(1.0, 0.06);
      if(stretch_reverse && forward){
        moveCubeForwardCurve();
      }
    }
    if(!forward){
      squash(0.5, 0.02);
      if(squash_stop)
        stretch(1.0, 0.06);
      if(stretch_reverse && !forward)
        moveCubeBackwardCurve();
    }
  }
  if (DISPLAY_CURVE)
    showCurve(curve1);
}

void scenario2(){
  straight_curve = true;
  qb.cubeAt(curve2, t);
  if (ENABLE_CUBE_MOVEMENT) {
    if(forward){
      squash(0.5, 0.02);
      if(squash_stop)
        stretch(1.0, 0.06);
      if(stretch_reverse && forward)
        moveCubeForwardCurve();
    }
    if(!forward)
      moveCubeBackwardCurve();

  }
  if (DISPLAY_CURVE)
    showCurve(curve2);
}

void scenario3(){
  dt = 0.01;
  straight_curve = true;
  qb.cubeAt(curve3, t);
  if (ENABLE_CUBE_MOVEMENT){
    if(forward)
      moveCubeForwardCurve();
    if(!forward)
      moveCubeBackwardCurve();
  }
  if (DISPLAY_CURVE)
    showCurve(curve3);
}

void scenario4(){

  qb.cubeAt(curve4, t);
  if (ENABLE_CUBE_MOVEMENT){
    if(forward)
      moveCubeForwardCurve();
    if(!forward)
      moveCubeForwardCurve();
  }
  if (DISPLAY_CURVE)
    showCurve(curve4);
}

void calmBoredom(){
  straight_curve = true;
  using_multiple_curves = true;
  curve_size = 4;
  dt = 0.01;

  if(t > 0.0-EPS && t < 0.25){
    qb.cubeAt(curvePath1, 4*t);
    if (ENABLE_CUBE_MOVEMENT){
      squash(0.2, 0.005);
      if(squash_stop)
        stretch(0.2, 0.01);
      if(stretch_reverse && forward){
        rotation(0.3, 0.01, 1);
        moveCubeForwardCurve();
      }
    }
  }
  else if(t > 0.25-EPS && t < 0.5){
    qb.cubeAt(curvePath2, 4*(t-0.25));
    if (ENABLE_CUBE_MOVEMENT){
      squash(0.2, 0.005);
      if(squash_stop)
        stretch(0.2, 0.01);
        if(stretch_reverse && forward){
          rotation(0.3, 0.01, 1);
          moveCubeForwardCurve();
        }
    }
  }
  else if(t > 0.5-EPS && t < 0.75){
    qb.cubeAt(curvePath3, 4*(t-0.5));
    if (ENABLE_CUBE_MOVEMENT){
      squash(0.2, 0.005);
      if(squash_stop)
        stretch(0.2, 0.01);
        if(stretch_reverse && forward){
          rotation(0.3, 0.01, 1);
          moveCubeForwardCurve();
        }
    }
  }
  else if(t > 0.75-EPS && t < 1+EPS){
    qb.cubeAt(curvePath4, 4*(t-0.75));
    if (ENABLE_CUBE_MOVEMENT){
      squash(0.2, 0.005);
      if(squash_stop)
        stretch(0.2, 0.01);
        if(stretch_reverse && forward){
          rotation(0.3, 0.01, 1);
          moveCubeForwardCurve();
        }
    }
  }
  if (DISPLAY_CURVE){
    showCurve(curvePath1);
    showCurve(curvePath2);
    showCurve(curvePath3);
    showCurve(curvePath4);
  }
}

void happiness(){
  using_multiple_curves = true;
  curve_size = 4;
  dt = 0.01;

  if(t > 0.0-EPS && t < 0.25){
    qb.cubeAt(curvePath1, 4*t);
    if (ENABLE_CUBE_MOVEMENT){
      squash(0.3, 0.03);
      if(squash_stop)
        stretch(0.3, 0.06);
      if(stretch_reverse && forward){
        moveCubeForwardCurve();
      }
    }
  }
  else if(t > 0.25-EPS && t < 0.5){
    qb.cubeAt(curvePath2, 4*(t-0.25));
    if (ENABLE_CUBE_MOVEMENT){
      squash(0.3, 0.03);
      if(squash_stop)
        stretch(0.3, 0.06);
      if(stretch_reverse && forward){
        moveCubeForwardCurve();
      }
    }
  }
  else if(t > 0.5-EPS && t < 0.75){
    qb.cubeAt(curvePath3, 4*(t-0.5));
    if (ENABLE_CUBE_MOVEMENT){
      squash(0.3, 0.03);
      if(squash_stop)
        stretch(0.3, 0.06);
      if(stretch_reverse && forward){
        moveCubeForwardCurve();
      }
    }
  }
  else if(t > 0.75-EPS && t < 1+EPS){
    qb.cubeAt(curvePath4, 4*(t-0.75));
    if (ENABLE_CUBE_MOVEMENT){
      squash(0.3, 0.03);
      if(squash_stop)
        stretch(0.3, 0.06);
      if(stretch_reverse && forward){
        moveCubeForwardCurve();
      }
    }
  }
  if (DISPLAY_CURVE){
    showCurve(curvePath1);
    showCurve(curvePath2);
    showCurve(curvePath3);
    showCurve(curvePath4);
  }
}

void excitement(){
  straight_curve = true;
  using_multiple_curves = true;
  curve_size = 4;
  dt = 0.01;

  if(t > 0.0-EPS && t < 0.25){
    qb.cubeAt(curvePath1, 4*t);
    if (ENABLE_CUBE_MOVEMENT){
      squash(0.3, 0.02);
      if(squash_stop)
        stretch(0.5, 0.05);
      if(stretch_reverse && forward){
        spin(12.56, 0.15);
        moveCubeForwardCurve();
      }
    }
  }
  else if(t > 0.25-EPS && t < 0.5){
    qb.cubeAt(curvePath2, 4*(t-0.25));
    if (ENABLE_CUBE_MOVEMENT){
      squash(0.3, 0.02);
      if(squash_stop)
        stretch(0.5, 0.05);
      if(stretch_reverse && forward){
        spin(12.56, 0.15);
        moveCubeForwardCurve();
      }
    }
  }
  else if(t > 0.5-EPS && t < 0.75){
    qb.cubeAt(curvePath3, 4*(t-0.5));
    if (ENABLE_CUBE_MOVEMENT){
      squash(0.3, 0.02);
      if(squash_stop)
        stretch(0.5, 0.05);
      if(stretch_reverse && forward){
        spin(12.56, 0.15);
        moveCubeForwardCurve();
      }
    }
  }
  else if(t > 0.75-EPS && t < 1+EPS){
    qb.cubeAt(curvePath4, 4*(t-0.75));
    if (ENABLE_CUBE_MOVEMENT){
      squash(0.3, 0.02);
      if(squash_stop)
        stretch(0.5, 0.05);
      if(stretch_reverse && forward){
        spin(12.56, 0.15);
        moveCubeForwardCurve();
      }
    }
  }
  if (DISPLAY_CURVE){
    showCurve(curvePath1);
    showCurve(curvePath2);
    showCurve(curvePath3);
    showCurve(curvePath4);
  }
}

void sadness(){
  using_multiple_curves = true;
  curve_size = 4;
  dt = 0.01;

  if(t > 0.0-EPS && t < 0.25){
    qb.cubeAt(curvePath1, 4*t);
    if (ENABLE_CUBE_MOVEMENT){
      tilt(0.8, 0.04, 0);
      squash(0.2, 0.005);
      if(squash_stop)
        stretch(0.2, 0.01);
      if(stretch_reverse && forward){
        rotation(0.3, 0.01, 1);
        moveCubeForwardCurve();
      }
    }
  }
  else if(t > 0.25-EPS && t < 0.5){
    qb.cubeAt(curvePath2, 4*(t-0.25));
    if (ENABLE_CUBE_MOVEMENT){
      tilt(0.8, 0.04, 0);
      squash(0.2, 0.005);
      if(squash_stop)
        stretch(0.2, 0.01);
        if(stretch_reverse && forward){
          rotation(0.3, 0.01, 1);
          moveCubeForwardCurve();
        }
    }
  }
  else if(t > 0.5-EPS && t < 0.75){
    qb.cubeAt(curvePath3, 4*(t-0.5));
    if (ENABLE_CUBE_MOVEMENT){
      tilt(0.8, 0.04, 0);
      squash(0.2, 0.005);
      if(squash_stop)
        stretch(0.2, 0.01);
        if(stretch_reverse && forward){
          rotation(0.3, 0.01, 1);
          moveCubeForwardCurve();
        }
    }
  }
  else if(t > 0.75-EPS && t < 1+EPS){
    qb.cubeAt(curvePath4, 4*(t-0.75));
    if (ENABLE_CUBE_MOVEMENT){
      tilt(0.8, 0.04, 0);
      squash(0.2, 0.005);
      if(squash_stop)
        stretch(0.2, 0.01);
        if(stretch_reverse && forward){
          rotation(0.3, 0.01, 1);
          moveCubeForwardCurve();
        }
    }
  }
  if (DISPLAY_CURVE){
    showCurve(curvePath1);
    showCurve(curvePath2);
    showCurve(curvePath3);
    showCurve(curvePath4);
  }
}

void anger(){
  straight_curve = true;
  using_multiple_curves = true;
  curve_size = 4;
  dt = 0.01;

  if(t > 0.0-EPS && t < 0.25){
    qb.cubeAt(curvePath1, 4*t);
    if (ENABLE_CUBE_MOVEMENT){
      shake(0.1);
      squash(0.3, 0.03);
      if(squash_stop)
        stretch(0.5, 0.05);
      if(stretch_reverse && forward){
        rotation(0.3, 0.01, 1);
        moveCubeForwardCurve();
      }
    }
  }
  else if(t > 0.25-EPS && t < 0.5){
    qb.cubeAt(curvePath2, 4*(t-0.25));
    if (ENABLE_CUBE_MOVEMENT){
      shake(0.1);
      squash(0.3, 0.03);
      if(squash_stop)
        stretch(0.5, 0.05);
      if(stretch_reverse && forward){
        rotation(0.3, 0.01, 1);
        moveCubeForwardCurve();
      }
    }
  }
  else if(t > 0.5-EPS && t < 0.75){
    qb.cubeAt(curvePath3, 4*(t-0.5));
    if (ENABLE_CUBE_MOVEMENT){
      shake(0.1);
      squash(0.3, 0.03);
      if(squash_stop)
        stretch(0.5, 0.05);
      if(stretch_reverse && forward){
        rotation(0.3, 0.01, 1);
        moveCubeForwardCurve();
      }
    }
  }
  else if(t > 0.75 && t < 1 + EPS){
    qb.cubeAt(curvePath4, 4*(t-0.75));
    if (ENABLE_CUBE_MOVEMENT){
      shake(0.1);
      squash(0.3, 0.03);
      if(squash_stop)
        stretch(0.5, 0.05);
      if(stretch_reverse && forward){
        moveCubeForwardCurve();
      }
    }
  }
  if (DISPLAY_CURVE){
    showCurve(curvePath1);
    showCurve(curvePath2);
    showCurve(curvePath3);
    showCurve(curvePath4);
  }
}

void fear(){
  straight_curve = true;
  using_multiple_curves = true;
  curve_size = 4;
  dt = 0.01;

  if(t > 0.0-EPS && t < 0.25){
    qb.cubeAt(curvePath1, 4*t);
    if (ENABLE_CUBE_MOVEMENT){
      tilt(0.5, 0.01, 1);
      shake(0.03);
      squash(0.2, 0.002);
      if(squash_stop)
        stretch(0.2, 0.004);
      if(stretch_reverse && forward){
        rotation(0.3, 0.01, 1);
        moveCubeForwardCurve();
      }
    }
  }
  else if(t > 0.25-EPS && t < 0.5){
    qb.cubeAt(curvePath2, 4*(t-0.25));
    if (ENABLE_CUBE_MOVEMENT){
      tilt(0.5, 0.01, 1);
      shake(0.03);
      squash(0.2, 0.002);
      if(squash_stop)
        stretch(0.2, 0.004);
      if(stretch_reverse && forward){
        rotation(0.3, 0.01, 1);
        moveCubeForwardCurve();
      }
    }
  }
  else if(t > 0.5-EPS && t < 0.75){
    qb.cubeAt(curvePath3, 4*(t-0.5));
    if (ENABLE_CUBE_MOVEMENT){
      tilt(0.5, 0.01, 1);
      shake(0.03);
      squash(0.2, 0.002);
      if(squash_stop)
        stretch(0.2, 0.004);
      if(stretch_reverse && forward){
        rotation(0.3, 0.01, 1);
        moveCubeForwardCurve();
      }
    }
  }
  else if(t > 0.75-EPS && t < 1+EPS){
    qb.cubeAt(curvePath4, 4*(t-0.75));
    if (ENABLE_CUBE_MOVEMENT){
      tilt(0.5, 0.01, 1);
      shake(0.03);
      squash(0.2, 0.004);
      if(squash_stop)
        stretch(0.2, 0.002);
      if(stretch_reverse && forward){
        rotation(0.3, 0.01, 1);
        moveCubeForwardCurve();
      }
    }
  }
  if (DISPLAY_CURVE){
    showCurve(curvePath1);
    showCurve(curvePath2);
    showCurve(curvePath3);
    showCurve(curvePath4);
  }
}

void calmSad(){
  straight_curve = true;
  using_multiple_curves = true;
  curve_size = 4;
  dt = 0.005;

  if(t > 0.0-EPS && t < 0.25){
    qb.cubeAt(curvePath1, 4*t);
    if (ENABLE_CUBE_MOVEMENT){
      squash(0.2, 0.005);
      if(squash_stop)
        stretch(0.2, 0.01);
      if(stretch_reverse && forward){
        rotation(0.3, 0.01, 1);
        moveCubeForwardCurve();
      }
    }
  }
  else if(t > 0.25-EPS && t < 0.5){
    qb.cubeAt(curvePath2, 4*(t-0.25));
    if (ENABLE_CUBE_MOVEMENT){
      squash(0.2, 0.005);
      if(squash_stop)
        stretch(0.2, 0.01);
      if(stretch_reverse && forward){
        rotation(0.3, 0.01, 1);
        moveCubeForwardCurve();
      }
    }
  }
  else if(t > 0.5-EPS && t < 0.75){
    qb.cubeAt(curvePath3, 4*(t-0.5));
    if (ENABLE_CUBE_MOVEMENT){
      tilt(0.8, 0.04, 0);
      squash(0.2, 0.005);
      if(squash_stop)
        stretch(0.2, 0.01);
        if(stretch_reverse && forward){
          rotation(0.3, 0.01, 1);
          moveCubeForwardCurve();
        }
    }
  }
  else if(t > 0.75-EPS && t < 1){
    qb.cubeAt(curvePath4, 4*(t-0.75));
    if (ENABLE_CUBE_MOVEMENT){
      tilt(0.8, 0.04, 0);
      squash(0.2, 0.005);
      if(squash_stop)
        stretch(0.2, 0.01);
        if(stretch_reverse && forward){
          rotation(0.3, 0.01, 1);
          moveCubeForwardCurve();
        }
    }
  }
  if (DISPLAY_CURVE){
    showCurve(curvePath1);
    showCurve(curvePath2);
    showCurve(curvePath3);
    showCurve(curvePath4);
  }
}

void excitedSadCalmAngry(){
  straight_curve = true;
  using_multiple_curves = true;
  curve_size = 4;
  dt = 0.01;

  if(t >= 0.0 && t <= 0.25){
    qb.cubeAt(curvePath1, 4*t);
    if (ENABLE_CUBE_MOVEMENT){
      squash(0.3, 0.01);
      if(squash_stop)
        stretch(0.5, 0.02);
      if(stretch_reverse && forward){
        spin(12.56, 0.15);
        moveCubeForwardCurve();
      }
    }
  }
  else if(t > 0.25-EPS && t < 0.5){
    qb.cubeAt(curvePath2, 4*(t-0.25));
    if (ENABLE_CUBE_MOVEMENT){
      tilt(0.8, 0.04, 0);
      squash(0.2, 0.005);
      if(squash_stop)
        stretch(0.2, 0.01);
      if(stretch_reverse && forward){
        rotation(0.3, 0.01, 1);
        moveCubeForwardCurve();
      }
    }
  }
  else if(t > 0.5-EPS && t < 0.75){
    qb.cubeAt(curvePath3, 4*(t-0.5));
    if (ENABLE_CUBE_MOVEMENT){
      if(tilt_stop)
        tiltBack();
      squash(0.2, 0.005);
      if(squash_stop)
        stretch(0.2, 0.01);
        if(stretch_reverse && forward){
          rotation(0.3, 0.01, 1);
          moveCubeForwardCurve();
        }
    }
  }
  else if(t > 0.75-EPS && t < 1){
    qb.cubeAt(curvePath4, 4*(t-0.75));
    if (ENABLE_CUBE_MOVEMENT){
      shake(0.1);
      squash(0.3, 0.01);
      if(squash_stop)
        stretch(0.5, 0.02);
      if(stretch_reverse && forward){
        rotation(0.3, 0.01, 1);
        moveCubeForwardCurve();
      }
    }
  }
  if (DISPLAY_CURVE){
    showCurve(curvePath1);
    showCurve(curvePath2);
    showCurve(curvePath3);
    showCurve(curvePath4);
  }
}

void switchEmotions(){

  if(key_switch != 1)
    straight_curve = true;
  else
    straight_curve = false;

  using_multiple_curves = true;
  curve_size = 10;
  dt = 0.01;

  if(t > 0.0-EPS && t < 0.1+EPS){
    qb.cubeAt(curvePath1, 10*t);
    if (ENABLE_CUBE_MOVEMENT){
      changeEmotions();
    }
  }
  else if(t > 0.1 && t < 0.2+EPS){
    qb.cubeAt(curvePath2, 10*(t-0.1));
    if (ENABLE_CUBE_MOVEMENT){
      changeEmotions();
    }
  }
  else if(t > 0.2 && t < 0.3+EPS){
    qb.cubeAt(curvePath3, 10*(t-0.2));
    if (ENABLE_CUBE_MOVEMENT){
      changeEmotions();
    }
  }
  else if(t > 0.3 && t < 0.4+EPS){
    qb.cubeAt(curvePath4, 10*(t-0.3));
    if (ENABLE_CUBE_MOVEMENT){
      changeEmotions();
    }
  }
  else if(t > 0.4 && t < 0.5+EPS){
    qb.cubeAt(curvePath5, 10*(t-0.4));
    if (ENABLE_CUBE_MOVEMENT){
      changeEmotions();
    }
  }
  else if(t > 0.5 && t < 0.6+EPS){
    qb.cubeAt(curvePath6, 10*(t-0.5));
    if (ENABLE_CUBE_MOVEMENT){
      changeEmotions();
    }
  }
  else if(t > 0.6 && t < 0.7+EPS){
    qb.cubeAt(curvePath7, 10*(t-0.6));
    if (ENABLE_CUBE_MOVEMENT){
      changeEmotions();
    }
  }
  else if(t > 0.7 && t < 0.8+EPS){
    qb.cubeAt(curvePath8, 10*(t-0.7));
    if (ENABLE_CUBE_MOVEMENT){
      changeEmotions();
    }
  }
  else if(t > 0.8 && t < 0.9+EPS){
    qb.cubeAt(curvePath9, 10*(t-0.8));
    if (ENABLE_CUBE_MOVEMENT){
      changeEmotions();
    }
  }
  else if(t > 0.9 && t < 1.0+EPS){
    qb.cubeAt(curvePath10, 10*(t-0.9));
    if (ENABLE_CUBE_MOVEMENT){
      changeEmotions();
    }
  }
  if (DISPLAY_CURVE){
    showCurve(curvePath1);
    showCurve(curvePath2);
    showCurve(curvePath3);
    showCurve(curvePath4);
    showCurve(curvePath5);
    showCurve(curvePath6);
    showCurve(curvePath7);
    showCurve(curvePath8);
    showCurve(curvePath9);
    showCurve(curvePath10);
  }
}
