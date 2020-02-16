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
  static std::vector<int> oldStates(11, GLFW_RELEASE);
  int newState;

  std::map<int,int> key_mappings = {
    {GLFW_KEY_ESCAPE, UNSELECT_OBJECT},
    {GLFW_KEY_1, SELECT_OBJECT_1},
    {GLFW_KEY_2, SELECT_OBJECT_2},
    {GLFW_KEY_3, SELECT_OBJECT_3},
    {GLFW_KEY_4, SELECT_OBJECT_4},
    {GLFW_KEY_5, SELECT_OBJECT_5},
    {GLFW_KEY_RIGHT, TRANSLATE_OBJECT_RIGHT},
    {GLFW_KEY_LEFT, TRANSLATE_OBJECT_LEFT},
    {GLFW_KEY_UP, TRANSLATE_OBJECT_UP},
    {GLFW_KEY_DOWN, TRANSLATE_OBJECT_DOWN},
    {GLFW_KEY_MINUS, SCALE_OBJECT_DOWN}
  };
  int i = 0;
  std::map<int, int>::iterator itr;
  for (itr = key_mappings.begin(); itr != key_mappings.end(); itr++) 
  {
    newState = glfwGetKey(window, itr->first);
    if( oldStates.at(i) == GLFW_PRESS && newState == GLFW_RELEASE)
    {
      oldStates.at(i) = newState;
      return itr->second;
    }
    oldStates.at(i) = newState;
    i++;
  }

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


