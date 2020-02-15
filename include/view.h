#ifndef VIEW_H
#define VIEW_H

//careful: no multiple declarations for glm allowed
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../include/camera.h"

extern Camera camera;

class View {
  public:
    GLFWwindow* initialize_window();
    void processInput(GLFWwindow *window);
    glm::mat4 getViewMatrix();
  private:
};
#endif

