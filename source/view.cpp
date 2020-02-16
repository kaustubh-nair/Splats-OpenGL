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
  static int oldState1 = GLFW_RELEASE;
  int newState = glfwGetKey(window, GLFW_KEY_ESCAPE) ;
  if (newState == GLFW_RELEASE && oldState1 == GLFW_PRESS)
    return UNSELECT_OBJECT;
  oldState1 = newState;

  newState = glfwGetKey(window, GLFW_KEY_1);
  static int oldState2 = GLFW_RELEASE;
   if (newState == GLFW_RELEASE && oldState1 == GLFW_PRESS)
    return SELECT_OBJECT_1;
  oldState1 = newState;

  static int oldState3 = GLFW_RELEASE;
   if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    return SELECT_OBJECT_2;
  oldState3 = newState;

  static int oldState4 = GLFW_RELEASE;
   if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    return SELECT_OBJECT_3;
  oldState4 = newState;

  static int oldState5 = GLFW_RELEASE;
   if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    return SELECT_OBJECT_4;
  oldState5 = newState;

  static int oldState6 = GLFW_RELEASE;
   if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    return SELECT_OBJECT_5;
  oldState6 = newState;

  static int oldState7 = GLFW_RELEASE;
   if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    return SELECT_OBJECT_5;
  oldState7 = newState;

  static int oldState8 = GLFW_RELEASE;
   if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    return SELECT_OBJECT_5;
  oldState8 = newState;

  static int oldState9 = GLFW_RELEASE;
  int newState9 = glfwGetKey(window, GLFW_KEY_UP);
   if (oldState9 == GLFW_PRESS && newState9 == GLFW_RELEASE)
    return SELECT_OBJECT_5;
  oldState9 = newState9;

  static int oldState11 = GLFW_RELEASE;
  int newState11 = glfwGetKey(window, GLFW_KEY_MINUS);
   if (oldState11 == GLFW_PRESS && newState11 == GLFW_RELEASE)
   {
      oldState11 = newState11;
     return SCALE_OBJECT_DOWN;
   }
  oldState11 = newState11;

  static int oldState10 = GLFW_RELEASE;
  int newState10 = glfwGetKey(window, GLFW_KEY_DOWN);
   if (oldState10 == GLFW_PRESS && newState10 == GLFW_RELEASE)
    return SELECT_OBJECT_5;
  oldState10 = newState10;


  static int oldState12 = GLFW_RELEASE;
   if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
    return SELECT_OBJECT_5;

  static int oldState13 = GLFW_RELEASE;
  int newState13 = glfwGetKey(window, GLFW_KEY_W);
   if (oldState13 == GLFW_PRESS && newState13 == GLFW_RELEASE)
  {
    GLint polygonMode;
    glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
    if ( polygonMode == GL_LINE )
      glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    else
      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  }
  oldState13 = newState13;

  return 0;
  
  /*
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
  {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    float x = xpos / (WIDTH * 0.5f) ;
    float y = ypos / (HEIGHT * 0.5f) ;

    glm::vec4 ray = glm::vec4(x,-y,0.0f,1.0f);

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);  
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 world = glm::inverse(proj * view);
    glm::vec4 worldPos = world * ray;
    //worldPos /= worldPos.w;

    objPosition = glm::vec3(worldPos.x, worldPos.y, 0.0f);
    //objPosition = glm::normalize(objPosition);
    print(objPosition.x);
    print(objPosition.y);
    return OBJECT_SELECTED;
  }*/
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


