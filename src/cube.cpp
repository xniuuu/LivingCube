#include "cube.h"

double cx = 0.0;
double cy = 0.0;

bool straight_curve = false;

double dt = 0.02;

void Cube::cubeAt( glm::vec4 (*path)(double), double timestep){

  path_point = path(timestep);
  //slope delta s
  glm::vec4 slope = path(timestep+dt) - path_point;
  //rotation angle
  glm::vec3 omega = glm::vec3(0.0, 0.0, 0.0);
  //rotation matrix
  glm::mat4 rot = glm::mat4(1.0);

  if(STATIC_CUBE || straight_curve){
    //cubes shape does not change unless using transformations
    for(int i = 0; i<4; ++i){

      double bend_y = ((i == 1 || i == 2)) ?  cy : 0.0;
      // Top edges
      v1.position = glm::vec4(path_point.x - 1.0            ,path_point.y + 1.0         , path_point.z - 1.0+(2.0*i/3.0)         , 1.0);
      v2.position = glm::vec4(path_point.x - 1.0+(2.0*i/3.0),path_point.y + 1.0 + bend_y, path_point.z + 1.0             + bend_y, 1.0);
      v3.position = glm::vec4(path_point.x + 1.0            ,path_point.y + 1.0         , path_point.z + 1.0-(2.0*i/3.0)         , 1.0);
      v4.position = glm::vec4(path_point.x + 1.0-(2.0*i/3.0),path_point.y + 1.0 + bend_y, path_point.z - 1.0             - bend_y, 1.0);

      // Bottom edges
      v5.position = glm::vec4(path_point.x - 1.0            , path_point.y - 1.0         , path_point.z - 1.0+(2.0*i/3.0)         , 1.0);
      v6.position = glm::vec4(path_point.x - 1.0+(2.0*i/3.0), path_point.y - 1.0 - bend_y, path_point.z + 1.0             + bend_y, 1.0);
      v7.position = glm::vec4(path_point.x + 1.0            , path_point.y - 1.0         , path_point.z + 1.0-(2.0*i/3.0)         , 1.0);
      v8.position = glm::vec4(path_point.x + 1.0-(2.0*i/3.0), path_point.y - 1.0 - bend_y, path_point.z - 1.0             - bend_y, 1.0);

      // Side edges
      if(ENABLE_CONTROLS && ENABLE_MOUSE_SCALING){
        double mouse_stretch = ((i == 1 || i == 2)) ?  std::abs(mouse_left_x) - std::abs(mouse_left_y)/1.5 : 0.0;
        v9.position  = glm::vec4(path_point.x - 1.0 - mouse_stretch, path_point.y + 1.0 - 2.0*i/3.0, path_point.z - 1.0 - mouse_stretch, 1.0);
        v10.position = glm::vec4(path_point.x - 1.0 - mouse_stretch, path_point.y + 1.0 - 2.0*i/3.0, path_point.z + 1.0 + mouse_stretch, 1.0);
        v11.position = glm::vec4(path_point.x + 1.0 + mouse_stretch, path_point.y + 1.0 - 2.0*i/3.0, path_point.z + 1.0 + mouse_stretch, 1.0);
        v12.position = glm::vec4(path_point.x + 1.0 + mouse_stretch, path_point.y + 1.0 - 2.0*i/3.0, path_point.z - 1.0 - mouse_stretch, 1.0);
      } else {
        double bend_x = ((i == 1 || i == 2)) ?  cx : 0.0;
        v9.position  = glm::vec4(path_point.x - 1.0 - bend_x, path_point.y + 1.0 - 2.0*i/3.0, path_point.z - 1.0 - bend_x, 1.0);
        v10.position = glm::vec4(path_point.x - 1.0 - bend_x, path_point.y + 1.0 - 2.0*i/3.0, path_point.z + 1.0 + bend_x, 1.0);
        v11.position = glm::vec4(path_point.x + 1.0 + bend_x, path_point.y + 1.0 - 2.0*i/3.0, path_point.z + 1.0 + bend_x, 1.0);
        v12.position = glm::vec4(path_point.x + 1.0 + bend_x, path_point.y + 1.0 - 2.0*i/3.0, path_point.z - 1.0 - bend_x, 1.0);
      }

      pos_l1[i]  = v1.position;
      pos_l2[i]  = v2.position;
      pos_l3[i]  = v3.position;
      pos_l4[i]  = v4.position;

      pos_l5[i]  = v5.position;
      pos_l6[i]  = v6.position;
      pos_l7[i]  = v7.position;
      pos_l8[i]  = v8.position;

      pos_l9[i]  = v9.position;
      pos_l10[i] = v10.position;
      pos_l11[i] = v11.position;
      pos_l12[i] = v12.position;
    }

    if(ENABLE_CUBE_MOVEMENT && ENABLE_CUBE_ROTATION && !(straight_curve) && timestep < (1.0-dt)){
      omega.x = (M_PI/2.0 - atan(slope.z / slope.y));
      omega.y = (M_PI/2.0 - atan(slope.z / slope.x));
      omega.z = (M_PI/2.0 - atan(slope.y / slope.x));
    }

    if(timestep > 0.0 && timestep < 1.0){
      rot = glm::translate(rot, glm::vec3(path_point.x, path_point.y, path_point.z));
      //rotation about z-axis and reset coordinates back to global corrdinates
      rot = glm::rotate(rot, -omega.z, glm::vec3(0.0, 0.0, 1.0));
      //rotation about y-axis
      rot = glm::rotate(rot, -omega.y, glm::vec3(1.0, 0.0, 0.0));
      //rotation about x-axis
      rot = glm::rotate(rot, -omega.x, glm::vec3(1.0, 0.0, 0.0));

      rot = glm::translate(rot, glm::vec3(-path_point.x, -path_point.y, -path_point.z));

      //apply rotation
      pos_l1  = rot * pos_l1;
      pos_l2  = rot * pos_l2;
      pos_l3  = rot * pos_l3;
      pos_l4  = rot * pos_l4;

      pos_l5  = rot * pos_l5;
      pos_l6  = rot * pos_l6;
      pos_l7  = rot * pos_l7;
      pos_l8  = rot * pos_l8;

      pos_l9  = rot * pos_l9;
      pos_l10 = rot * pos_l10;
      pos_l11 = rot * pos_l11;
      pos_l12 = rot * pos_l12;
    }
  }
  else{
    //cube also bends along the curve
    glm::vec4 path_point_top = path(timestep + N*dt);
    glm::vec4 path_point_mid = glm::vec4(0.0, 0.0, 0.0, 0.0);

    //slope vectors
    glm::vec4 slope_top = path(timestep + N*dt) - path(timestep + (N-1)*dt);
    glm::vec4 slope_bot = path(timestep+dt) - path_point;
    glm::vec4 slope_mid = glm::vec4(0.0, 0.0, 0.0, 0.0);

    //perpendicular vectors
    glm::vec3 perp_top = glm::vec3(slope_top.y, -slope_top.x, 0.0);
    glm::vec3 perp_bot = glm::vec3(slope_bot.y, -slope_bot.x, 0.0);
    glm::vec3 perp_mid = glm::vec3(0.0, 0.0, 0.0);

    //normalize perpendicular vectors
    perp_top = glm::normalize(perp_top);
    perp_bot = glm::normalize(perp_bot);

    for(int i = 0; i<4; ++i){
      v1.position = glm::vec4(path_point_top.x + perp_top.x                  , path_point_top.y + perp_top.y                  , path_point_top.z - 1.0+(2.0*i/3.0), 1.0);
      v2.position = glm::vec4(path_point_top.x + perp_top.x*(1.0 - 2.0*i/3.0), path_point_top.y + perp_top.y*(1.0 - 2.0*i/3.0), path_point_top.z + 1.0            , 1.0);
      v3.position = glm::vec4(path_point_top.x - perp_top.x                  , path_point_top.y - perp_top.y                  , path_point_top.z + 1.0-(2.0*i/3.0), 1.0);
      v4.position = glm::vec4(path_point_top.x - perp_top.x*(1.0 - 2.0*i/3.0), path_point_top.y - perp_top.y*(1.0 - 2.0*i/3.0), path_point_top.z - 1.0            , 1.0);

      v5.position = glm::vec4(path_point.x + perp_bot.x                  , path_point.y + perp_bot.y                  , path_point.z - 1.0+(2.0*i/3.0), 1.0);
      v6.position = glm::vec4(path_point.x + perp_bot.x*(1.0 - 2.0*i/3.0), path_point.y + perp_bot.y*(1.0 - 2.0*i/3.0), path_point.z + 1.0            , 1.0);
      v7.position = glm::vec4(path_point.x - perp_bot.x                  , path_point.y - perp_bot.y                  , path_point.z + 1.0-(2.0*i/3.0), 1.0);
      v8.position = glm::vec4(path_point.x - perp_bot.x*(1.0 - 2.0*i/3.0), path_point.y - perp_bot.y*(1.0 - 2.0*i/3.0), path_point.z - 1.0            , 1.0);

      if(i == 0){
        v9.position  = glm::vec4(path_point.x + perp_bot.x, path_point.y + perp_bot.y, path_point.z - 1.0, 1.0);
        v10.position = glm::vec4(path_point.x + perp_bot.x, path_point.y + perp_bot.y, path_point.z + 1.0, 1.0);
        v11.position = glm::vec4(path_point.x - perp_bot.x, path_point.y - perp_bot.y, path_point.z + 1.0, 1.0);
        v12.position = glm::vec4(path_point.x - perp_bot.x, path_point.y - perp_bot.y, path_point.z - 1.0, 1.0);
      } else if(i == 3) {
        v9.position  = glm::vec4(path_point_top.x + perp_top.x, path_point_top.y + perp_top.y, path_point_top.z - 1.0, 1.0);
        v10.position = glm::vec4(path_point_top.x + perp_top.x, path_point_top.y + perp_top.y, path_point_top.z + 1.0, 1.0);
        v11.position = glm::vec4(path_point_top.x - perp_top.x, path_point_top.y - perp_top.y, path_point_top.z + 1.0, 1.0);
        v12.position = glm::vec4(path_point_top.x - perp_top.x, path_point_top.y - perp_top.y, path_point_top.z - 1.0, 1.0);
      } else{
        path_point_mid = path(timestep + (i*N/3)*dt);
        slope_mid = path(timestep + (i*N/3 + 1)*dt) - path_point_mid;
        perp_mid = glm::vec3(slope_mid.y, -slope_mid.x, 0.0);
        perp_mid = glm::normalize(perp_mid);

        v9.position  = glm::vec4(path_point_mid.x + perp_mid.x, path_point_mid.y + perp_mid.y, path_point_mid.z - 1.0, 1.0);
        v10.position = glm::vec4(path_point_mid.x + perp_mid.x, path_point_mid.y + perp_mid.y, path_point_mid.z + 1.0, 1.0);
        v11.position = glm::vec4(path_point_mid.x - perp_mid.x, path_point_mid.y - perp_mid.y, path_point_mid.z + 1.0, 1.0);
        v12.position = glm::vec4(path_point_mid.x - perp_mid.x, path_point_mid.y - perp_mid.y, path_point_mid.z - 1.0, 1.0);
      }

      pos_l1[i]  = v1.position;
      pos_l2[i]  = v2.position;
      pos_l3[i]  = v3.position;
      pos_l4[i]  = v4.position;

      pos_l5[i]  = v5.position;
      pos_l6[i]  = v6.position;
      pos_l7[i]  = v7.position;
      pos_l8[i]  = v8.position;

      pos_l9[i]  = v9.position;
      pos_l10[i] = v10.position;
      pos_l11[i] = v11.position;
      pos_l12[i] = v12.position;
    }
  }
}

void Cube::drawCube(){
  double y = 0;
  double dy = 0.0001;
  int n = (int) 1/dy;

  glBegin(GL_POINTS);
  glColor3f(COLOR_CUBE);
  for(int i = 0; i < n; ++i){
      glVertex4fv(glm::value_ptr(evaluateCurve(pos_l1, y)));
      glVertex4fv(glm::value_ptr(evaluateCurve(pos_l2, y)));
      glVertex4fv(glm::value_ptr(evaluateCurve(pos_l3, y)));
      glVertex4fv(glm::value_ptr(evaluateCurve(pos_l4, y)));

      glVertex4fv(glm::value_ptr(evaluateCurve(pos_l5, y)));
      glVertex4fv(glm::value_ptr(evaluateCurve(pos_l6, y)));
      glVertex4fv(glm::value_ptr(evaluateCurve(pos_l7, y)));
      glVertex4fv(glm::value_ptr(evaluateCurve(pos_l8, y)));

      glVertex4fv(glm::value_ptr(evaluateCurve(pos_l9,  y)));
      glVertex4fv(glm::value_ptr(evaluateCurve(pos_l10, y)));
      glVertex4fv(glm::value_ptr(evaluateCurve(pos_l11, y)));
      glVertex4fv(glm::value_ptr(evaluateCurve(pos_l12, y)));

      y+=dy;
  }
  glEnd();
  glFlush();
}
