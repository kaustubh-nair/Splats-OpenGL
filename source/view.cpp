#include "../include/view.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Camera camera;
float WIDTH = 800.0f;
float HEIGHT = 600.0f;

GLFWwindow* View::initialize_window()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "yolo", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(0);
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  glewExperimental = GL_TRUE; 
  if ( GLEW_OK != glewInit() )
  {
    std::cout << "Glew failed" << std::endl;
    glfwTerminate();
    exit(0);
  }

  glViewport(0, 0, WIDTH, HEIGHT);
  return window;
}

glm::mat4 View::getViewMatrix()
{
  return camera.getViewMatrix();
}

int View::listenToCallbacks(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
  {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    float x = xpos / (WIDTH * 0.5f) - 1.0f;
    float y = ypos / (HEIGHT * 0.5f) - 1.0f;

    glm::vec4 ray = glm::vec4(x,y,0.0f,1.0f);

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);  
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 world = glm::inverse(proj * view);
    glm::vec4 screenPos = glm::vec4(x, -y, 1.0f, 1.0f);
    glm::vec4 worldPos = world * screenPos;

    objPosition = glm::normalize(worldPos);
    return OBJECT_SELECTED;
  }
  

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


