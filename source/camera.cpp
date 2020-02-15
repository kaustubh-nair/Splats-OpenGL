#include "../include/camera.h"

glm::mat4 Camera::getViewMatrix()
{
  return glm::lookAt(position, position + front, up);
}

Camera::Camera()
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    speed = 0.05;

    firstMouse = true;
    yaw   = -90.0f;	
    pitch =  0.0f;
    lastX =  800.0f / 2.0;
    lastY =  600.0 / 2.0;
    fov   =  45.0f;
}
