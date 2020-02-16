#ifndef CAMERA_H
#define CAMERA_H


//careful: no multiple declarations for glm allowed
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <string>
#include <vector>
#include <iostream>

#include "../include/vertex.h"
#include "../include/definitions.h"

class Camera {
  public:
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 front;

    Camera();
    glm::mat4 getViewMatrix();
};


#endif
