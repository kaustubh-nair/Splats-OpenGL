#include "../include/controller.h"
#include<cmath>

void Controller::mainLoop( void )
{
  glewExperimental = GL_TRUE;
  if( GLEW_OK !=glewInit())
    print("GLEW initialization failed!");


  GLFWwindow* window = this->mainWindow;

  /* load ply files into model */
  //std::vector<std::string> filepaths = { "data/beethoven.ply" };
  //std::vector<glm::vec3> meshPos = {glm::vec3(0.0f,0.0f,0.0f)};
  std::vector<std::string> filepaths = {"data/beethoven.ply", "data/fracttree.ply", "data/teapot.ply" , "data/big_spider.ply"};
  std::vector<glm::vec3> meshPos = {glm::vec3(0.0f,0.0f,3.0f), glm::vec3(-200.0f,-200.0f,0.0f), glm::vec3(200.0f,-200.0f,0.0f), glm::vec3(200.0f,200.0f,0.0f)};
  model.setup(filepaths, meshPos);

  /* setup shaders */
  Shader shader("source/shaders/shader.vs", "source/shaders/shader.fs");
  Shader lightingShader("source/shaders/lighting_shader.vs", "source/shaders/lighting_shader.fs");
  Shader normalColoringShader("source/shaders/normal_coloring_shader.vs", "source/shaders/normal_coloring_shader.fs");

   glm::mat4 proj = glm::ortho(-(WIDTH / 2.0f), WIDTH / 2.0f,
                               -(HEIGHT / 2.0f),HEIGHT / 2.0f,
                               -100.0f, 100.0f);
  glm::mat4 viewMatrix = view.getViewMatrix();

  glEnable(GL_DEPTH_TEST);

  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

  while(!glfwWindowShouldClose(window))
  {

    int ret = view.listenToCallbacks(window);
    glm::vec2 dir = view.listenToMouseCallbacks(window);

    reactToCallback(ret);

    glClearColor(0.1f,0.1f,0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    viewMatrix = view.getViewMatrix();

    if(this->normalColoring)
      normalColoringShader.use();
    else
    {
      shader.use();
    }
    shader.setMat4("projection", proj);
    shader.setMat4("view", viewMatrix);
    shader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
    shader.setVec3("lightPos",90.5f, 90.5f, 90.0f );

    model.draw(shader, lightingShader);

    lightingShader.use();
    lightingShader.setMat4("projection", proj);
    lightingShader.setMat4("view", viewMatrix);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
}


void Controller::reactToCallback(int ret)
{
  switch(ret)
  {
    case UNSELECT_OBJECT:
        model.unselect();
        break;
    case SELECT_OBJECT_1:
        model.select(1);
        break;
    case SELECT_OBJECT_2:
        model.select(2);
        break;
    case SELECT_OBJECT_3:
        model.select(3);
        break;
    case SELECT_OBJECT_4:
        model.select(4);
        break;
    case SCALE_OBJECT_DOWN:
        model.scale(DOWN);
        break;
    case SCALE_OBJECT_UP:
        model.scale(UP);
        break;
    case TOGGLE_SPLATS:
        model.renderSplats = !model.renderSplats;
        model.refresh();
        break;
    case TOGGLE_WIREFRAME:
        this->toggleWireframe();
        break;
    case INCREASE_SPLAT_RADIUS:
        model.changeSplatRadius(UP);
        break;
    case DECREASE_SPLAT_RADIUS:
        model.changeSplatRadius(DOWN);
        break;
    case TOGGLE_NORMAL_COLORING:
        this->normalColoring = !this->normalColoring;
        break;
    case TRANSLATE_OBJECT:
        model.translate(view.direction);
        break;
    case ROTATE_OBJECT:
        model.rotate(view.trackball, view.direction);
        break;
  }
}

void Controller::toggleWireframe()
{
  GLint polygonMode[2];
  glGetIntegerv(GL_POLYGON_MODE, polygonMode);
  if ( polygonMode[0] == GL_LINE )
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
  else
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}
