#include "animations.h"

bool reverse = false;
bool forward = true;
bool using_multiple_curves = false;

double t = 0.0;

double squash_magnitude = 0.0;
bool squash_reverse = false;
bool squash_stop = false;

double stretch_magnitude = 0.0;
bool stretch_reverse = false;
bool stretch_stop = false;

float rotation_angle = 0.0;
bool rotate_back = false;
bool rotation_stop = false;

float spin_angle = 0.0;

float shake_magnitude = 0.0;
bool scale_back = false;

double breath_const = 0.0;
bool breathe_in = true;

double tilt_measure = 0.0;
bool tilt_stop = false;

int curve_size = 0;

Cube qb;

void moveCubeForwardCurve(){

  if(STATIC_CUBE || straight_curve){
    if (straight_curve && t > 1.0 - EPS){
      if(using_multiple_curves)
        t = 0;
      else
        forward = false;
      squash_stop = false;
      squash_reverse = false;
      stretch_stop = false;
      stretch_reverse = false;
      rotation_stop = false;
      rotate_back = false;
    }
    else if (!straight_curve && (t + dt > 1.0 - EPS)){
      if(using_multiple_curves)
        t = 0;
      else
        forward = false;
      squash_stop = false;
      squash_reverse = false;
      stretch_stop = false;
      stretch_reverse = false;
      rotation_stop = false;
      rotate_back = false;
    }
    else
      t += dt;

    if(using_multiple_curves && curve_size == 4){
      if( ((t > 0.25 - EPS) && (t < 0.25 + EPS)) || ((t > 0.5 - EPS) && (t < 0.5 + EPS)) || ((t > 0.75 - EPS) && (t < 0.75 + EPS)) ){
        squash_stop = false;
        squash_reverse = false;
        stretch_stop = false;
        stretch_reverse = false;
        rotation_stop = false;
        rotate_back = false;
      }
    }

    if(using_multiple_curves && curve_size == 10){
      if( ((t > 0.1 - EPS) && (t < 0.1 + EPS)) || ((t > 0.2 - EPS) && (t < 0.2 + EPS)) || ((t > 0.3 - EPS) && (t < 0.3 + EPS)) ||
          ((t > 0.4 - EPS) && (t < 0.4 + EPS)) || ((t > 0.5 - EPS) && (t < 0.5 + EPS)) || ((t > 0.6 - EPS) && (t < 0.6 + EPS)) ||
          ((t > 0.7 - EPS) && (t < 0.7 + EPS)) || ((t > 0.8 - EPS) && (t < 0.8 + EPS)) || ((t > 0.9 - EPS) && (t < 0.9 + EPS)) ){
        squash_stop = false;
        squash_reverse = false;
        stretch_stop = false;
        stretch_reverse = false;
        rotation_stop = false;
        rotate_back = false;
      }
    }
  }

  if(!STATIC_CUBE && !straight_curve) {
    if (t > (1.0 - N*dt) - EPS) {
      t = 1.0 - N*dt;
    }
    else{
      t += dt;
    }
  }
}

void moveCubeBackwardCurve(){
  if (t < dt){
    //std::cout << qb.v5.position.y << " " << qb.v6.position.y << " " << qb.v7.position.y << " " << qb.v8.position.y<<std::endl;
    t = 0;
    forward = true;
    squash_stop = false;
    squash_reverse = false;
    stretch_stop = false;
    stretch_reverse = false;
    rotation_stop = false;
    rotate_back = false;
  }
  else{
    t -= dt;
  }
}

void squash(double squash_th, double speed){

  if(squash_magnitude > squash_th)
    squash_reverse = 1;

  if(squash_magnitude < 0.0 && squash_reverse)
    squash_stop = 1;

  glm::mat4 scale = glm::mat4(1.0);

  if(direction_start.x > direction_start.y && direction_start.y < dt){
    cy = squash_magnitude;
    cx = 0;
    scale = glm::translate(scale, glm::vec3(qb.path_point.x-squash_magnitude, qb.path_point.y, qb.path_point.z));
    scale = glm::scale(scale, glm::vec3(1.0-squash_magnitude, 1.0+squash_magnitude/2.0, 1.0+squash_magnitude/2.0));
    scale = glm::translate(scale, glm::vec3(-qb.path_point.x, -qb.path_point.y, -qb.path_point.z));
  }
  else{
    cx = squash_magnitude;
    cy = 0;
    scale = glm::translate(scale, glm::vec3(qb.path_point.x, qb.path_point.y-squash_magnitude, qb.path_point.z));
    scale = glm::scale(scale, glm::vec3(1.0+squash_magnitude/2.0, 1.0-squash_magnitude, 1.0+squash_magnitude/2.0));
    scale = glm::translate(scale, glm::vec3(-qb.path_point.x, -qb.path_point.y, -qb.path_point.z));
  }

  qb.pos_l1  = scale * qb.pos_l1;
  qb.pos_l2  = scale * qb.pos_l2;
  qb.pos_l3  = scale * qb.pos_l3;
  qb.pos_l4  = scale * qb.pos_l4;

  qb.pos_l5  = scale * qb.pos_l5;
  qb.pos_l6  = scale * qb.pos_l6;
  qb.pos_l7  = scale * qb.pos_l7;
  qb.pos_l8  = scale * qb.pos_l8;

  qb.pos_l9  = scale * qb.pos_l9;
  qb.pos_l10 = scale * qb.pos_l10;
  qb.pos_l11 = scale * qb.pos_l11;
  qb.pos_l12 = scale * qb.pos_l12;

  if(squash_reverse)
    squash_magnitude -= speed*3;
  else if (!squash_reverse)
    squash_magnitude += speed;

  if (squash_stop){
    squash_magnitude = 0;
  }
}

void stretch(double stretch_th, double speed){

  if(stretch_magnitude > stretch_th)
    stretch_reverse = 1;

  if(stretch_magnitude < 0.0 && stretch_reverse)
    stretch_stop = 1;

  glm::mat4 scale = glm::mat4(1.0);

  if(direction_start.x > direction_start.y && direction_start.y < dt){
    cy = -stretch_magnitude/5.0;
    cx = 0;
    scale = glm::translate(scale, glm::vec3(qb.path_point.x+stretch_magnitude, qb.path_point.y, qb.path_point.z));
    scale = glm::scale(scale, glm::vec3(1.0+stretch_magnitude, 1.0-stretch_magnitude/5.0, 1.0-stretch_magnitude/5.0));
    scale = glm::translate(scale, glm::vec3(-qb.path_point.x, -qb.path_point.y, -qb.path_point.z));
  }
  else{
    cx = -stretch_magnitude/3.0;
    cy = 0;
    scale = glm::translate(scale, glm::vec3(qb.path_point.x, qb.path_point.y+stretch_magnitude, qb.path_point.z));
    scale = glm::scale(scale, glm::vec3(1.0-stretch_magnitude/5.0, 1.0+stretch_magnitude, 1.0-stretch_magnitude/5.0));
    scale = glm::translate(scale, glm::vec3(-qb.path_point.x, -qb.path_point.y, -qb.path_point.z));
  }

  qb.pos_l1  = scale * qb.pos_l1;
  qb.pos_l2  = scale * qb.pos_l2;
  qb.pos_l3  = scale * qb.pos_l3;
  qb.pos_l4  = scale * qb.pos_l4;

  qb.pos_l5  = scale * qb.pos_l5;
  qb.pos_l6  = scale * qb.pos_l6;
  qb.pos_l7  = scale * qb.pos_l7;
  qb.pos_l8  = scale * qb.pos_l8;

  qb.pos_l9  = scale * qb.pos_l9;
  qb.pos_l10 = scale * qb.pos_l10;
  qb.pos_l11 = scale * qb.pos_l11;
  qb.pos_l12 = scale * qb.pos_l12;

  if(stretch_reverse)
    stretch_magnitude -= 2*speed;
  else if(!stretch_reverse)
    stretch_magnitude += speed;

  if(stretch_stop){
    stretch_magnitude = 0.0;
  }
}

void rotation(double rot_th, double speed, int dir){
  if(rotation_angle > rot_th)
    rotate_back = 1;

  if(rotation_angle < 0.0+EPS && rotate_back)
    rotation_stop = 1;

  glm::mat4 rot = glm::mat4(1.0);
  rot = glm::translate(rot, glm::vec3(qb.path_point.x, qb.path_point.y, qb.path_point.z));
  switch(dir) {
    case 1: rot = glm::rotate(rot, rotation_angle, glm::vec3(0.0, 0.0, 1.0)); break;
    case 2: rot = glm::rotate(rot, -rotation_angle, glm::vec3(0.0, 0.0, 1.0)); break;
    default: rot = glm::rotate(rot, rotation_angle, glm::vec3(0.0, 0.0, 1.0)); break;
  }
  rot = glm::translate(rot, glm::vec3(-qb.path_point.x, -qb.path_point.y, -qb.path_point.z));

  qb.pos_l1  = rot * qb.pos_l1;
  qb.pos_l2  = rot * qb.pos_l2;
  qb.pos_l3  = rot * qb.pos_l3;
  qb.pos_l4  = rot * qb.pos_l4;

  qb.pos_l5  = rot * qb.pos_l5;
  qb.pos_l6  = rot * qb.pos_l6;
  qb.pos_l7  = rot * qb.pos_l7;
  qb.pos_l8  = rot * qb.pos_l8;

  qb.pos_l9  = rot * qb.pos_l9;
  qb.pos_l10 = rot * qb.pos_l10;
  qb.pos_l11 = rot * qb.pos_l11;
  qb.pos_l12 = rot * qb.pos_l12;

  if(rotate_back)
    rotation_angle -= speed/3.0;
  else if(!rotate_back)
    rotation_angle += speed;

  if(rotation_stop){
    rotation_angle = 0;
  }
}

void spin(double spin_th, double speed){

  if(spin_angle > spin_th)
    spin_angle = 0;

  glm::mat4 rot = glm::mat4(1.0);
  rot = glm::translate(rot, glm::vec3(qb.path_point.x, qb.path_point.y, qb.path_point.z));
  rot = glm::rotate(rot, spin_angle, glm::vec3(0.0, 1.0, 0.0));
  rot = glm::translate(rot, glm::vec3(-qb.path_point.x, -qb.path_point.y, -qb.path_point.z));

  qb.pos_l1  = rot * qb.pos_l1;
  qb.pos_l2  = rot * qb.pos_l2;
  qb.pos_l3  = rot * qb.pos_l3;
  qb.pos_l4  = rot * qb.pos_l4;

  qb.pos_l5  = rot * qb.pos_l5;
  qb.pos_l6  = rot * qb.pos_l6;
  qb.pos_l7  = rot * qb.pos_l7;
  qb.pos_l8  = rot * qb.pos_l8;

  qb.pos_l9  = rot * qb.pos_l9;
  qb.pos_l10 = rot * qb.pos_l10;
  qb.pos_l11 = rot * qb.pos_l11;
  qb.pos_l12 = rot * qb.pos_l12;

  spin_angle += speed;
}

void shake(double shake_th){

  if(shake_magnitude > shake_th-EPS)
    scale_back = 1;

  if(shake_magnitude < 0+EPS && scale_back)
    scale_back = 0;

  glm::mat4 scale = glm::mat4(1.0);

  scale = glm::translate(scale, glm::vec3(qb.path_point.x + stretch_magnitude, qb.path_point.y, qb.path_point.z));
  scale = glm::scale(scale, glm::vec3(1.0 + shake_magnitude, 1.0 + shake_magnitude, 1.0 + shake_magnitude));
  scale = glm::translate(scale, glm::vec3(-qb.path_point.x, -qb.path_point.y, -qb.path_point.z));

  qb.pos_l1  = scale * qb.pos_l1;
  qb.pos_l2  = scale * qb.pos_l2;
  qb.pos_l3  = scale * qb.pos_l3;
  qb.pos_l4  = scale * qb.pos_l4;

  qb.pos_l5  = scale * qb.pos_l5;
  qb.pos_l6  = scale * qb.pos_l6;
  qb.pos_l7  = scale * qb.pos_l7;
  qb.pos_l8  = scale * qb.pos_l8;

  qb.pos_l9  = scale * qb.pos_l9;
  qb.pos_l10 = scale * qb.pos_l10;
  qb.pos_l11 = scale * qb.pos_l11;
  qb.pos_l12 = scale * qb.pos_l12;

  if(scale_back)
    shake_magnitude -= 0.1;
  else
    shake_magnitude += 0.05;

}

void idleBreathing(){

  if(breath_const > 0.1)
    breathe_in = false;

  if(breath_const < -0.1)
    breathe_in = true;

  cx = 3*breath_const;

  glm::mat4 scale = glm::mat4(1.0);

  if(breath_const > 0.0){
    scale = glm::translate(scale, glm::vec3(qb.path_point.x, qb.path_point.y, qb.path_point.z));
    scale = glm::scale(scale, glm::vec3(1.0+breath_const, 1.0+breath_const, 1.0+breath_const));
    scale = glm::translate(scale, glm::vec3(-qb.path_point.x, -qb.path_point.y, -qb.path_point.z));

  } else {
    scale = glm::translate(scale, glm::vec3(qb.path_point.x, qb.path_point.y, qb.path_point.z));
    scale = glm::scale(scale, glm::vec3(1.0+breath_const/2, 1.0+breath_const/2, 1.0+breath_const/2));
    scale = glm::translate(scale, glm::vec3(-qb.path_point.x, -qb.path_point.y, -qb.path_point.z));
  }

  qb.pos_l1  = scale * qb.pos_l1;
  qb.pos_l2  = scale * qb.pos_l2;
  qb.pos_l3  = scale * qb.pos_l3;
  qb.pos_l4  = scale * qb.pos_l4;

  qb.pos_l5  = scale * qb.pos_l5;
  qb.pos_l6  = scale * qb.pos_l6;
  qb.pos_l7  = scale * qb.pos_l7;
  qb.pos_l8  = scale * qb.pos_l8;

  qb.pos_l9  = scale * qb.pos_l9;
  qb.pos_l10 = scale * qb.pos_l10;
  qb.pos_l11 = scale * qb.pos_l11;
  qb.pos_l12 = scale * qb.pos_l12;

  if(breathe_in)
    breath_const += 0.002;
  else
    breath_const -= 0.001;
}

void tilt(double tilt_th, double speed, bool direction){

  if(!direction && tilt_measure > tilt_th-EPS){
    tilt_measure = tilt_th;
  }

  if(direction && tilt_measure < -tilt_th+EPS){
    tilt_measure = -tilt_th;
  }

  if(tilt_measure > tilt_th-EPS)
    tilt_stop = true;

  glm::vec3 slope = glm::vec3(tilt_measure, 1.0, 0.0);
  glm::vec3 perp = glm::vec3(1.0, -tilt_measure, 0.0);
  perp = glm::normalize(perp);

  for(int i = 0; i<4; ++i){
    qb.v1.position = glm::vec4(qb.path_point.x + tilt_measure + perp.x                  , qb.path_point.y + 1.0 + perp.y                  , qb.path_point.z - 1.0+(2.0*i/3.0), 1.0);
    qb.v2.position = glm::vec4(qb.path_point.x + tilt_measure + perp.x*(1.0 - 2.0*i/3.0), qb.path_point.y + 1.0 + perp.y*(1.0 - 2.0*i/3.0), qb.path_point.z + 1.0            , 1.0);
    qb.v3.position = glm::vec4(qb.path_point.x + tilt_measure - perp.x                  , qb.path_point.y + 1.0 - perp.y                  , qb.path_point.z + 1.0-(2.0*i/3.0), 1.0);
    qb.v4.position = glm::vec4(qb.path_point.x + tilt_measure - perp.x*(1.0 - 2.0*i/3.0), qb.path_point.y + 1.0 - perp.y*(1.0 - 2.0*i/3.0), qb.path_point.z - 1.0            , 1.0);

    qb.v5.position = glm::vec4(qb.path_point.x - 1.0            , qb.path_point.y - 1.0, qb.path_point.z - 1.0+(2.0*i/3.0), 1.0);
    qb.v6.position = glm::vec4(qb.path_point.x - 1.0+(2.0*i/3.0), qb.path_point.y - 1.0, qb.path_point.z + 1.0            , 1.0);
    qb.v7.position = glm::vec4(qb.path_point.x + 1.0            , qb.path_point.y - 1.0, qb.path_point.z + 1.0-(2.0*i/3.0), 1.0);
    qb.v8.position = glm::vec4(qb.path_point.x + 1.0-(2.0*i/3.0), qb.path_point.y - 1.0, qb.path_point.z - 1.0            , 1.0);

    if(i == 0){
      qb.v9.position  = glm::vec4(qb.path_point.x + tilt_measure - perp.x, qb.path_point.y + 1.0 - perp.y, qb.path_point.z - 1.0, 1.0);
      qb.v10.position = glm::vec4(qb.path_point.x + tilt_measure - perp.x, qb.path_point.y + 1.0 - perp.y, qb.path_point.z + 1.0, 1.0);
      qb.v11.position = glm::vec4(qb.path_point.x + tilt_measure + perp.x, qb.path_point.y + 1.0 + perp.y, qb.path_point.z + 1.0, 1.0);
      qb.v12.position = glm::vec4(qb.path_point.x + tilt_measure + perp.x, qb.path_point.y + 1.0 + perp.y, qb.path_point.z - 1.0, 1.0);
    } else{
      double bend_x = ((i == 1 || i == 2)) ?  cx : 0.0;
      //std::cout << dx<< std::endl;
      qb.v9.position  = glm::vec4(qb.path_point.x - 1.0 - bend_x, qb.path_point.y + 1.0 - 2.0*i/3.0, qb.path_point.z - 1.0 - bend_x, 1.0);
      qb.v10.position = glm::vec4(qb.path_point.x - 1.0 - bend_x, qb.path_point.y + 1.0 - 2.0*i/3.0, qb.path_point.z + 1.0 + bend_x, 1.0);
      qb.v11.position = glm::vec4(qb.path_point.x + 1.0 + bend_x, qb.path_point.y + 1.0 - 2.0*i/3.0, qb.path_point.z + 1.0 + bend_x, 1.0);
      qb.v12.position = glm::vec4(qb.path_point.x + 1.0 + bend_x, qb.path_point.y + 1.0 - 2.0*i/3.0, qb.path_point.z - 1.0 - bend_x, 1.0);
    }

    qb.pos_l1[i]  = qb.v1.position;
    qb.pos_l2[i]  = qb.v2.position;
    qb.pos_l3[i]  = qb.v3.position;
    qb.pos_l4[i]  = qb.v4.position;

    qb.pos_l5[i]  = qb.v5.position;
    qb.pos_l6[i]  = qb.v6.position;
    qb.pos_l7[i]  = qb.v7.position;
    qb.pos_l8[i]  = qb.v8.position;

    qb.pos_l9[i]  = qb.v9.position;
    qb.pos_l10[i] = qb.v10.position;
    qb.pos_l11[i] = qb.v11.position;
    qb.pos_l12[i] = qb.v12.position;
  }

  if(!direction)
    tilt_measure += speed;
  if(direction)
    tilt_measure -= speed;
}

void tiltBack(){

    if(tilt_measure < 0+EPS && tilt_measure > 0){
      tilt_stop = false;
      return;
    }

    if(tilt_measure > 0)
      tilt_measure -= 0.05;
    else if(tilt_measure < 0)
      tilt_measure += 0.05;

    glm::vec3 slope = glm::vec3(tilt_measure, 1.0, 0.0);
    glm::vec3 perp = glm::vec3(1.0, -tilt_measure, 0.0);
    perp = glm::normalize(perp);

    for(int i = 0; i<4; ++i){
      qb.v1.position = glm::vec4(qb.path_point.x + tilt_measure + perp.x                  , qb.path_point.y + 1.0 + perp.y                  , qb.path_point.z - 1.0+(2.0*i/3.0), 1.0);
      qb.v2.position = glm::vec4(qb.path_point.x + tilt_measure + perp.x*(1.0 - 2.0*i/3.0), qb.path_point.y + 1.0 + perp.y*(1.0 - 2.0*i/3.0), qb.path_point.z + 1.0            , 1.0);
      qb.v3.position = glm::vec4(qb.path_point.x + tilt_measure - perp.x                  , qb.path_point.y + 1.0 - perp.y                  , qb.path_point.z + 1.0-(2.0*i/3.0), 1.0);
      qb.v4.position = glm::vec4(qb.path_point.x + tilt_measure - perp.x*(1.0 - 2.0*i/3.0), qb.path_point.y + 1.0 - perp.y*(1.0 - 2.0*i/3.0), qb.path_point.z - 1.0            , 1.0);

      qb.v5.position = glm::vec4(qb.path_point.x - 1.0            , qb.path_point.y - 1.0, qb.path_point.z - 1.0+(2.0*i/3.0), 1.0);
      qb.v6.position = glm::vec4(qb.path_point.x - 1.0+(2.0*i/3.0), qb.path_point.y - 1.0, qb.path_point.z + 1.0            , 1.0);
      qb.v7.position = glm::vec4(qb.path_point.x + 1.0            , qb.path_point.y - 1.0, qb.path_point.z + 1.0-(2.0*i/3.0), 1.0);
      qb.v8.position = glm::vec4(qb.path_point.x + 1.0-(2.0*i/3.0), qb.path_point.y - 1.0, qb.path_point.z - 1.0            , 1.0);

      if(i == 0){
        qb.v9.position  = glm::vec4(qb.path_point.x + tilt_measure - perp.x, qb.path_point.y + 1.0 - perp.y, qb.path_point.z - 1.0, 1.0);
        qb.v10.position = glm::vec4(qb.path_point.x + tilt_measure - perp.x, qb.path_point.y + 1.0 - perp.y, qb.path_point.z + 1.0, 1.0);
        qb.v11.position = glm::vec4(qb.path_point.x + tilt_measure + perp.x, qb.path_point.y + 1.0 + perp.y, qb.path_point.z + 1.0, 1.0);
        qb.v12.position = glm::vec4(qb.path_point.x + tilt_measure + perp.x, qb.path_point.y + 1.0 + perp.y, qb.path_point.z - 1.0, 1.0);
      } else{
        double bend_x = ((i == 1 || i == 2)) ?  cx : 0.0;
        //std::cout << dx<< std::endl;
        qb.v9.position  = glm::vec4(qb.path_point.x - 1.0 - bend_x, qb.path_point.y + 1.0 - 2.0*i/3.0, qb.path_point.z - 1.0 - bend_x, 1.0);
        qb.v10.position = glm::vec4(qb.path_point.x - 1.0 - bend_x, qb.path_point.y + 1.0 - 2.0*i/3.0, qb.path_point.z + 1.0 + bend_x, 1.0);
        qb.v11.position = glm::vec4(qb.path_point.x + 1.0 + bend_x, qb.path_point.y + 1.0 - 2.0*i/3.0, qb.path_point.z + 1.0 + bend_x, 1.0);
        qb.v12.position = glm::vec4(qb.path_point.x + 1.0 + bend_x, qb.path_point.y + 1.0 - 2.0*i/3.0, qb.path_point.z - 1.0 - bend_x, 1.0);
      }

      qb.pos_l1[i]  = qb.v1.position;
      qb.pos_l2[i]  = qb.v2.position;
      qb.pos_l3[i]  = qb.v3.position;
      qb.pos_l4[i]  = qb.v4.position;

      qb.pos_l5[i]  = qb.v5.position;
      qb.pos_l6[i]  = qb.v6.position;
      qb.pos_l7[i]  = qb.v7.position;
      qb.pos_l8[i]  = qb.v8.position;

      qb.pos_l9[i]  = qb.v9.position;
      qb.pos_l10[i] = qb.v10.position;
      qb.pos_l11[i] = qb.v11.position;
      qb.pos_l12[i] = qb.v12.position;
    }
}
