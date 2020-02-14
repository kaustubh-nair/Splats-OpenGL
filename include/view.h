#ifndef VIEW_H
#define VIEW_H
//
//careful: no multiple declarations for glm allowed
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class View {
  public:
    View();
    GLFWwindow* initialize_window();
  private:
};
#endif

