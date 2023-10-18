#ifndef SPLINE_H
#define SPLINE_H

#include "opengl.h"
#include "../config.h"
#include <cmath>

/*control point */
using ctrl_pt = glm::vec4;

/*these vectors are used to determine whether a curve is more vertically or horizontally oriented */
extern glm::vec4 direction_start;
extern glm::vec4 direction_end;

/*function that displays a path with a single curve*/
void showCurve( glm::vec4 (*path)(double));

/*formula that evaluates a point in the Bézier curve, see (insert paper chapter here) for more details*/
glm::vec4 evaluateCurve(glm::mat4 p, double t);

/*different kind of Bézier curves */
glm::vec4 curve1(double t);
glm::vec4 curve2(double t);
glm::vec4 curve3(double t);
glm::vec4 curve4(double t);

/*All of these curves form a path;
  to extend the path, add a curve at the last control point of the last curve (current last curve: curve_10)*/
glm::vec4 curvePath1(double t);
glm::vec4 curvePath2(double t);
glm::vec4 curvePath3(double t);
glm::vec4 curvePath4(double t);
glm::vec4 curvePath5(double t);
glm::vec4 curvePath6(double t);
glm::vec4 curvePath7(double t);
glm::vec4 curvePath8(double t);
glm::vec4 curvePath9(double t);
glm::vec4 curvePath10(double t);

#endif
