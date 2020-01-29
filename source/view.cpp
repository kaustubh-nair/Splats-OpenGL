#include "../include/view.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

View::View()
{
}

GLFWwindow* View::initialize_window()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "yolo", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(0);
  }
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE; 
  if ( GLEW_OK != glewInit() )
  {
    std::cout << "Glew failed" << std::endl;
    glfwTerminate();
    exit(0);
  }


  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
