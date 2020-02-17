#include "../include/camera.h"

glm::mat4 Camera::getViewMatrix()
{
  return glm::lookAt(position, position + front, up);
}

Camera::Camera()
{
  position = glm::vec3(0.0f,0.0f,6.0f);
  front = glm::vec3(0.0f,0.0f, -1.0f);
  up = glm::vec3(0.0f, 1.0f, 0.0f);
}
