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

#define OBJECT_SELECTED 1;

extern Camera camera;
extern float WIDTH;
extern float HEIGHT;

class View {
  public:
    glm::vec3 objPosition;  //temporary variable to store selected object position
    GLFWwindow* initialize_window();
    int listenToCallbacks(GLFWwindow *window);
    glm::mat4 getViewMatrix();
  private:
};
#endif

