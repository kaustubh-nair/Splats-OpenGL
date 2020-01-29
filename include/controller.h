#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/glew.h>
#include <iostream>

#include "../include/view.h"


class Controller {
  public:
    View *view = nullptr;
    GLFWwindow* mainWindow = nullptr;

    Controller();
    ~Controller();
    void mainLoop();
};

void processInput(GLFWwindow* window);
#endif

