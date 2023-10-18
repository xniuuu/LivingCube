// Enable and disable features

/*Value 0 or 1: enables or disables scaling using the mouse*/
#define ENABLE_CONTROLS 1
  #define ENABLE_MOUSE_SCALING 0

/*Value 0 or 1: If set to 1 -> cube also bends along the curve
                If set to 0 -> cube does not bend along the curve
  for straight paths, or paths with multiple curves, this feature is disabled */
#define STATIC_CUBE 1

/*Value 0 or 1: If set to 1 -> cube moves along the path
                If set to 0 -> cube stays at the beginning of a path */
#define ENABLE_CUBE_MOVEMENT 1
  /*Values 0 or 1: If set to 1 -> cube also rotates according to the slope at each timestep
                   If set to 0 -> cube ignores the slope */
  #define ENABLE_CUBE_ROTATION 1
  /*Value 0 or 1: Disables or enables animation loop */
  #define ENABLE_MOVEMENT_LOOP 1

/*Value 0 or 1: Disables or enables the camera to follow the cube */
#define CAMERA_FOLLOW 1

/*Value 0 or 1: Disables or enables display of the current path */
#define DISPLAY_CURVE 1

/*Values 1 to 13, scenario description below */
#define SELECT_SCENARIO 5
  /* scenario 0: curve1 scenario; single curve
     scenario 1: curve2 scenario; single curve
     scenario 2: curve3 scenario; single curve
     scenario 3: curve4 scenario; single curve
     scenario 4: calm or bored cube; 4 curves
     scenario 5: happy cube; 4 curves
     scenario 6: excited cube; 4 curves
     scenario 7: sad cube; 4 curves
     scenario 8: angry cube; 4 curves
     scenario 9: scared cube; 4 curves
     scenario 10: calm/bored, then sad; 4 curves
     scenario 11: happy, sad, calm/bored, angry; 4 curves
     scenario 12: changeable emotions; 10 curves

     default:  scenario 13
  */

/*See (paper chapter) for details;
  change it according to a path, s.t. the object still looks like a cube */
#define N 8

/*Set preferences for color of the cube and path */
#define COLOR_CURVE 1.0, 0.0, 1.0
#define COLOR_CUBE 1.0, 1.0, 1.0
