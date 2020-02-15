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
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 front = glm::vec3(0.0f, 1.0f, 0.0f);
    float speed = 0.05;

    bool firstMouse = true;
    float yaw   = -90.0f;	
    float pitch =  0.0f;
    float lastX =  800.0f / 2.0;
    float lastY =  600.0 / 2.0;
    float fov   =  45.0f;

    Camera();
    glm::mat4 getViewMatrix();
};


#endif
