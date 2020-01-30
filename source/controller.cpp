#include "../include/controller.h"

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

void Controller::processInput(GLFWwindow* window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
