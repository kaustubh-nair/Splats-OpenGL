#include "../include/controller.h"


Controller::Controller( void ) 
{
  this->view = new View();
  this->mainWindow = this->view->initialize_window();
}

Controller::~Controller( void )
{
  delete this->view;
}

void Controller::mainLoop( void )
{
  GLFWwindow* window = this->mainWindow;

  while(!glfwWindowShouldClose(window))
  {
    processInput(window);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
}

void processInput(GLFWwindow* window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
