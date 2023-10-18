#ifndef OPENGL_H
#define OPENGL_H

#include <iostream>
#include <stdio.h>
#include <limits>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#define GL_GLEXT_PROTOTYPES

/*This is used for comparing doubles/floats */
#define EPS 100*std::numeric_limits<double>::epsilon()

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif



#endif
