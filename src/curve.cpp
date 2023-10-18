#include "curve.h"

glm::vec4 direction_start;
glm::vec4 direction_end;

void showCurve( glm::vec4 (*path)(double)){
  double y = 0;
  double dy = 0.001;
  int n = (int) 1/dy;

  glBegin(GL_POINTS);
  glColor3f(COLOR_CURVE);
  for(int i = 0; i < n; ++i){
      //display Curve
      glVertex4fv(glm::value_ptr(path(y)));
      y+=dy;
  }
  glEnd();
  glFlush();
}

glm::vec4 evaluateCurve(glm::mat4 p, double t){
  double b1 = (1-t)*(1-t)*(1-t);
  double b2 = 3*t*(1-t)*(1-t);
  double b3 = 3*t*t*(1-t);
  double b4 = t*t*t;

  glm::vec4 b(b1, b2, b3, b4);

  glm::vec4 q = p*b;
  return q;
}

glm::vec4 curve1(double t){
  ctrl_pt down_left, down_right, up_left, up_right;
  glm::mat4 p;

  down_left = glm::vec4(-2.5, 0.0, 0.0, 1.0);
  down_right = glm::vec4(-2.5, 5.0, 0.0, 1.0);
  up_left = glm::vec4(2.5, 5.0, 0.0, 1.0);
  up_right = glm::vec4(2.5, 0.0, 0.0, 1.0);

  p[0] = down_left;
  p[1] = down_right;
  p[2] = up_left;
  p[3] = up_right;

  direction_start = evaluateCurve(p, 0.01) - evaluateCurve(p, 0);
  direction_end = evaluateCurve(p, 1) - evaluateCurve(p, 0.99);

  return evaluateCurve(p, t);
}

glm::vec4 curve2(double t){
  ctrl_pt top, mid1, mid2, bot;
  glm::mat4 p;

  top  = glm::vec4(0.0,-3.0, 0.0, 1.0);
  mid1 = glm::vec4(0.0, 2.2, 0.0, 1.0);
  mid2 = glm::vec4(0.0, 2.8, 0.0, 1.0);
  bot  = glm::vec4(0.0, 3.0, 0.0, 1.0);

  p[0] = top;
  p[1] = mid1;
  p[2] = mid2;
  p[3] = bot;

  direction_start = evaluateCurve(p, 0.01) - evaluateCurve(p, 0);
  direction_end = evaluateCurve(p, 1) - evaluateCurve(p, 0.99);

  return evaluateCurve(p, t);
}

glm::vec4 curve3(double t){
  ctrl_pt left, mid1, mid2, right;
  glm::mat4 p;

  left = glm::vec4(-3.0, 0.0, 0.0, 1.0);
  mid1 = glm::vec4(-1.0, 0.0, 0.0, 1.0);
  mid2 = glm::vec4( 1.0, 0.0, 0.0, 1.0);
  right = glm::vec4(3.0, 0.0, 0.0, 1.0);

  p[0] = left;
  p[1] = mid1;
  p[2] = mid2;
  p[3] = right;

  direction_start = evaluateCurve(p, 0.01) - evaluateCurve(p, 0);
  direction_end = evaluateCurve(p, 1) - evaluateCurve(p, 0.99);

  return evaluateCurve(p, t);
}

glm::vec4 curve4(double t){
  ctrl_pt down_left, down_right, up_left, up_right;
  glm::mat4 p;

  down_left = glm::vec4(-3.0, 0.0, 0.0, 1.0);
  down_right = glm::vec4(-2.8, 1.0, 0.0, 1.0);
  up_left = glm::vec4(-2.0, 2.0, 0.0, 1.0);
  up_right = glm::vec4(2.0, 0.0, 0.0, 1.0);

  p[0] = down_left;
  p[1] = down_right;
  p[2] = up_left;
  p[3] = up_right ;

  direction_start = evaluateCurve(p, 0.01) - evaluateCurve(p, 0);
  direction_end = evaluateCurve(p, 1) - evaluateCurve(p, 0.99);

  return evaluateCurve(p, t);

}

glm::vec4 curvePath1(double t){

  ctrl_pt p0, p1, p2, p3;
  glm::mat4 p;

  p[0] = glm::vec4(0.0, 0   , 0, 1.0);
  p[1] = glm::vec4(1.0, 1.0, 0, 1.0);
  p[2] = glm::vec4(2.0, 1.0, 0, 1.0);
  p[3] = glm::vec4(3.0, 0   , 0, 1.0);

  direction_start = evaluateCurve(p, 0.01) - evaluateCurve(p, 0);
  direction_end = evaluateCurve(p, 1) - evaluateCurve(p, 0.99);

  return evaluateCurve(p, t);
}

glm::vec4 curvePath2(double t){
  ctrl_pt p0, p1, p2, p3;
  glm::mat4 p;

  p[0] = glm::vec4(3.0, 0, 0, 1.0);
  p[1] = glm::vec4(4.0, 1.0, 0, 1.0);
  p[2] = glm::vec4(5.0, 1.0, 0, 1.0);
  p[3] = glm::vec4(6.0, 0, 0, 1.0);

  direction_start = evaluateCurve(p, 0.01) - evaluateCurve(p, 0);
  direction_end = evaluateCurve(p, 1) - evaluateCurve(p, 0.99);

  return evaluateCurve(p, t);
}

glm::vec4 curvePath3(double t){
  ctrl_pt p0, p1, p2, p3;
  glm::mat4 p;

  p[0] = glm::vec4(6.0, 0, 0, 1.0);
  p[1] = glm::vec4(7.0, 1.0, 0, 1.0);
  p[2] = glm::vec4(8.0, 1.0, 0, 1.0);
  p[3] = glm::vec4(9.0, 0, 0, 1.0);

  direction_start = evaluateCurve(p, 0.01) - evaluateCurve(p, 0);
  direction_end = evaluateCurve(p, 1) - evaluateCurve(p, 0.99);

  return evaluateCurve(p, t);
}

glm::vec4 curvePath4(double t){
  ctrl_pt p0, p1, p2, p3;
  glm::mat4 p;

  p[0] = glm::vec4(9.0 , 0, 0, 1.0);
  p[1] = glm::vec4(10.0, 1.0, 0, 1.0);
  p[2] = glm::vec4(11.0, 1.0, 0, 1.0);
  p[3] = glm::vec4(12.0, 0, 0, 1.0);

  direction_start = evaluateCurve(p, 0.01) - evaluateCurve(p, 0);
  direction_end = evaluateCurve(p, 1) - evaluateCurve(p, 0.99);

  return evaluateCurve(p, t);
}

glm::vec4 curvePath5(double t){
  ctrl_pt p0, p1, p2, p3;
  glm::mat4 p;

  p[0] = glm::vec4(12.0, 0, 0, 1.0);
  p[1] = glm::vec4(13.0, 1.0, 0, 1.0);
  p[2] = glm::vec4(14.0, 1.0, 0, 1.0);
  p[3] = glm::vec4(15.0, 0, 0, 1.0);

  direction_start = evaluateCurve(p, 0.01) - evaluateCurve(p, 0);
  direction_end = evaluateCurve(p, 1) - evaluateCurve(p, 0.99);

  return evaluateCurve(p, t);
}

glm::vec4 curvePath6(double t){
  ctrl_pt p0, p1, p2, p3;
  glm::mat4 p;

  p[0] = glm::vec4(15.0, 0, 0, 1.0);
  p[1] = glm::vec4(16.0, 1.0, 0, 1.0);
  p[2] = glm::vec4(17.0, 1.0, 0, 1.0);
  p[3] = glm::vec4(18.0, 0, 0, 1.0);

  direction_start = evaluateCurve(p, 0.01) - evaluateCurve(p, 0);
  direction_end = evaluateCurve(p, 1) - evaluateCurve(p, 0.99);

  return evaluateCurve(p, t);
}

glm::vec4 curvePath7(double t){
  ctrl_pt p0, p1, p2, p3;
  glm::mat4 p;

  p[0] = glm::vec4(18.0, 0, 0, 1.0);
  p[1] = glm::vec4(19.0, 1.0, 0, 1.0);
  p[2] = glm::vec4(20.0, 1.0, 0, 1.0);
  p[3] = glm::vec4(21.0, 0, 0, 1.0);

  direction_start = evaluateCurve(p, 0.01) - evaluateCurve(p, 0);
  direction_end = evaluateCurve(p, 1) - evaluateCurve(p, 0.99);

  return evaluateCurve(p, t);
}

glm::vec4 curvePath8(double t){
  ctrl_pt p0, p1, p2, p3;
  glm::mat4 p;

  p[0] = glm::vec4(21.0, 0, 0, 1.0);
  p[1] = glm::vec4(22.0, 1.0, 0, 1.0);
  p[2] = glm::vec4(23.0, 1.0, 0, 1.0);
  p[3] = glm::vec4(24.0, 0, 0, 1.0);

  direction_start = evaluateCurve(p, 0.01) - evaluateCurve(p, 0);
  direction_end = evaluateCurve(p, 1) - evaluateCurve(p, 0.99);

  return evaluateCurve(p, t);
}

glm::vec4 curvePath9(double t){
  ctrl_pt p0, p1, p2, p3;
  glm::mat4 p;

  p[0] = glm::vec4(24.0, 0, 0, 1.0);
  p[1] = glm::vec4(25.0, 1.0, 0, 1.0);
  p[2] = glm::vec4(26.0, 1.0, 0, 1.0);
  p[3] = glm::vec4(27.0, 0, 0, 1.0);

  direction_start = evaluateCurve(p, 0.01) - evaluateCurve(p, 0);
  direction_end = evaluateCurve(p, 1) - evaluateCurve(p, 0.99);

  return evaluateCurve(p, t);
}

glm::vec4 curvePath10(double t){
  ctrl_pt p0, p1, p2, p3;
  glm::mat4 p;

  p[0] = glm::vec4(27.0, 0, 0, 1.0);
  p[1] = glm::vec4(28.0, 1.0, 0, 1.0);
  p[2] = glm::vec4(29.0, 1.0, 0, 1.0);
  p[3] = glm::vec4(30.0, 0, 0, 1.0);

  direction_start = evaluateCurve(p, 0.01) - evaluateCurve(p, 0);
  direction_end = evaluateCurve(p, 1) - evaluateCurve(p, 0.99);

  return evaluateCurve(p, t);
}
