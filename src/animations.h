#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "cube.h"

/*Used on paths with a single curve: this allows the cube to move back along the curve*/
extern bool reverse;
extern bool forward;

/*checks, if the current path is made of a single curve or multiple curves */
extern bool using_multiple_curves;

/*t ranges from 0 to 1, see (insert paper chapter) for more details */
extern double t;

/*variables used for squashing the cube, see (insert paper chapter) for more details */
extern double squash_magnitude;
extern bool squash_reverse;
extern bool squash_stop;

/*variables used for stretching the cube, see (insert paper chapter) for more details */
extern double stretch_magnitude;
extern bool stretch_reverse;
extern bool stretch_stop;

/*variables used for rotating the cube, see (insert paper chapter) for more details */
extern float rotation_angle;
extern bool rotate_back;
extern bool rotation_stop;

/*variable used for spinning the cube, see (insert paper chapter) for more details */
extern float spin_angle;

/*variable used for shake the cube, see (insert paper chapter) for more details */
extern float shake_magnitude;
extern bool scale_back;

/*variables used for sidle breathing of the cube, can be enabled by setting ENABLE_CUBE_MOVEMENT to 0;
  for more details, see (insert paper chapter) for more details */
extern double breath_const;
extern bool breathe_in;

/*variable used fto tilt the cube, see (insert paper chapter) for more details */
extern double tilt_measure;
extern bool tilt_stop;

/*stores, how many curves form a path*/
extern int curve_size;

extern Cube qb;

/*Default path: sungle curve, 4, curves, 10 curves. If you want to use another number of curves,
  you have to modify moveCubeForwardCurve(), s.t. the cube takes a stop at i/N
  i = ith curve; N = number of curves
  details are explained in (insert chapter from paper here)*/

/*Moves the cube forward along a path */
void moveCubeForwardCurve();

/*Moves the cube backwards along a path */
void moveCubeBackwardCurve();

/*Idle breathing of the cube */
void idleBreathing();

/*squashes the cube in x or y direction, at a given speed and down to a certain scaling
  for more details, see (paper chapter) */
void squash(double squash_th, double speed);

/*stretches the cube in x or y direction, at a given speed and up to a certain scaling
  for more details, see (paper chapter) */
void stretch(double stretch_th, double speed);

/*rotates the cube about the given axis at a given angle, speed */
void rotation(double rot_th, double speed, int dir);

/*spins the cube up to a given angle, at a given speed
  for more details, see (paper chapter) */
void spin(double spin_th, double speed);
void shake(double shake_th);

/*direction = 0 -> forward; direction = 1 -> back;
  tilts the cube, i.e. moves the top edges;
  for more details, see (paper chapter) */
void tilt(double tilt_th, double speed, bool direction);
void tiltBack();

#endif
