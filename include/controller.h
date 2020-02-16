#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/glew.h>
#include <iostream>

#include "../include/view.h"
#include "../include/shader.h"
#include "../include/model.h"
#include "../include/camera.h"
#include "../include/mesh.h"
#include "../include/ply_parser.h"

class Controller {
  public:
    View view;
    Model model;
    GLFWwindow* mainWindow = nullptr;

    Controller()
    {
      this->mainWindow = this->view.initialize_window();
    };

    ~Controller()
    {
    };

    void mainLoop();
    void reactToCallback(int ret);

  private:
};


#endif
