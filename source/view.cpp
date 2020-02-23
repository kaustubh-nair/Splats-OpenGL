#include "../include/view.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Camera camera;
float WIDTH = 800.0f;
float HEIGHT = 600.0f;
bool firstMouse;

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

  std::map<int,int> key_mappings = {
    {GLFW_KEY_ESCAPE, UNSELECT_OBJECT},
    {GLFW_KEY_1, SELECT_OBJECT_1},
    {GLFW_KEY_2, SELECT_OBJECT_2},
    {GLFW_KEY_3, SELECT_OBJECT_3},
    {GLFW_KEY_4, SELECT_OBJECT_4},
    {GLFW_KEY_5, SELECT_OBJECT_5},
    {GLFW_KEY_MINUS, SCALE_OBJECT_DOWN},
    {GLFW_KEY_S, TOGGLE_SPLATS},
    {GLFW_KEY_W, TOGGLE_WIREFRAME},
    {GLFW_KEY_J, DECREASE_SPLAT_RADIUS},
    {GLFW_KEY_K, INCREASE_SPLAT_RADIUS},
    {GLFW_KEY_N, TOGGLE_NORMAL_COLORING},

  };

  static std::vector<int> oldStates(key_mappings.size(), GLFW_RELEASE);
  int newState;

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
  newState = glfwGetKey(window, GLFW_KEY_EQUAL);
  if(oldState12 == GLFW_PRESS && newState == GLFW_RELEASE &&  glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
  {
     oldState12 = newState;
     return SCALE_OBJECT_UP;
  }
  oldState12 = newState;
  
  /* object picking */
  /*
  static int oldState13 = GLFW_RELEASE;
  newState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  if( oldState13 == GLFW_PRESS && newState == GLFW_RELEASE)
  {
    oldState13 = newState;
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    float x = xpos / (WIDTH * 0.5f) ;
    float y = ypos / (HEIGHT * 0.5f) ;

    glm::vec4 ray = glm::vec4(x,-y,0.0f,1.0f);

    glm::mat4 proj = glm::ortho(-(WIDTH / 2.0f), WIDTH / 2.0f,
                               -(HEIGHT / 2.0f),HEIGHT / 2.0f,
                               -100.0f, 100.0f);
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 worldInv = glm::inverse(proj * view);
    glm::vec4 worldPos = worldInv * ray;

    objPosition = glm::vec3(worldPos.x, worldPos.y, 0.0f);
    //objPosition = glm::normalize(objPosition);
    print(objPosition.x);
    print(objPosition.y);
    return OBJECT_SELECTED;
  }
  oldState13 = newState;
  */

  /* translation and rotation callbacks */
  int leftState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  int rightState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
  static double oldX, oldY;

  if(leftState == GLFW_RELEASE && rightState == GLFW_RELEASE)
    glfwGetCursorPos(window, &oldX, &oldY);

  if(rightState == GLFW_RELEASE)
    trackball.rotate(0,0,0,0);

  if(leftState == GLFW_PRESS)
  {
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    if(firstMouse)
    {
      oldX = x;
      oldY = y;
      firstMouse = false;
    }

    direction = glm::vec2(x - oldX, oldY - y);
    oldX = x;
    oldY = y;
    return TRANSLATE_OBJECT;
  }


  if(rightState == GLFW_PRESS)
  {
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    if(firstMouse)
    {
      oldX = x;
      oldY = y;
      firstMouse = false;
    }

    trackball.rotate((2.0 * oldX - WIDTH) / float(WIDTH),
    (HEIGHT - 2.0 * oldY) / float(HEIGHT),
    (2.0 * x - WIDTH) / float(WIDTH),
    (HEIGHT - 2.0 * y) / float(HEIGHT));
    direction = glm::vec2(x - oldX, oldY - y);
    oldX = x;
    oldY = y;
    return ROTATE_OBJECT;
  }

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}
