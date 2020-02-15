#include "../include/view.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

Camera camera;

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
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  glewExperimental = GL_TRUE; 
  if ( GLEW_OK != glewInit() )
  {
    std::cout << "Glew failed" << std::endl;
    glfwTerminate();
    exit(0);
  }


  glViewport(0, 0, 800, 600);
  return window;
}

glm::mat4 View::getViewMatrix()
{
  return camera.getViewMatrix();
}

void View::processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.position += camera.speed * camera.front;

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.position -= camera.speed * camera.front;

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.position -= glm::normalize(glm::cross(camera.front, camera.up)) * camera.speed;

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.position += glm::normalize(glm::cross(camera.front, camera.up)) * camera.speed;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
  if (camera.firstMouse)
  {
    camera.lastX = xpos;
    camera.lastY = ypos;
    camera.firstMouse = false;
  }

  float xoffset = xpos - camera.lastX;
  float yoffset = camera.lastY - ypos; // reversed since y-coordinates go from bottom to top
  camera.lastX = xpos;
  camera.lastY = ypos;

  float sensitivity = 0.1f; // change this value to your liking
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  camera.yaw += xoffset;
  camera.pitch += yoffset;

  // make sure that when camera.pitch is out of bounds, screen doesn't get flipped
  if (camera.pitch > 89.0f)
    camera.pitch = 89.0f;
  if (camera.pitch < -89.0f)
    camera.pitch = -89.0f;

  glm::vec3 front;
  front.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
  front.y = sin(glm::radians(camera.pitch));
  front.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
  camera.front = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  if (camera.fov >= 1.0f && camera.fov <= 45.0f)
    camera.fov -= yoffset;
  if (camera.fov <= 1.0f)
    camera.fov = 1.0f;
  if (camera.fov >= 45.0f)
    camera.fov = 45.0f;
}
