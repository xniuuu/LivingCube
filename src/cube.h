#ifndef CUBE_H
#define CUBE_H

#include "curve.h"
#include "controls.h"

/*controls the sides during stretching and squashing */
extern double cx, cy;

/*checks, whether the cube also rotates along the curve */
extern bool straight_curve;

/*timestep;
  if the cube has to move faster, increase dt
  if the cube has to move slower, decrease dt */
extern double dt;

/*describes a control point of the cube */
struct Point{
  glm::vec4 position;
};

class Cube{
public:
  /*stores the current control point of an edge*/
  Point v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12;

  /*4x4 matrix that stores all 4 control points of each edge*/
  glm::mat4 pos_l1, pos_l2, pos_l3, pos_l4, pos_l5, pos_l6, pos_l7, pos_l8,
            pos_l9, pos_l10, pos_l11, pos_l12;

  /*stores the current position of the cube;
    the position refers to the center of the cube*/
  glm::vec4 path_point;

  /*places the cube on a point of the path with the given timestep */
  void cubeAt(glm::vec4 (*path)(double), double timestep);

  /*draw the cube using glVertex4fv()
    OpenGL functions: glVertex4fv() */
  void drawCube();
};

#endif
