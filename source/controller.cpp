#include "../include/controller.h"
#include<cmath>

void Controller::mainLoop( void )
{
  glewExperimental = GL_TRUE;
  if( GLEW_OK !=glewInit())
    print("GLEW initialization failed!");


  GLFWwindow* window = this->mainWindow;

  Model model;

  /* load ply files into model */
  //std::vector<std::string> filepaths = { "data/sphere.ply" };
  //std::vector<glm::vec3> meshPos = {glm::vec3(0.0f,0.0f,-3.0f)};
  std::vector<std::string> filepaths = {"data/beethoven.ply", "data/shark.ply", "data/apple.ply" , "data/big_spider.ply"};
  std::vector<glm::vec3> meshPos = {glm::vec3(0.01f,0.0f,0.0f), glm::vec3(2.5f,0.0f,0.0f), glm::vec3(-2.5f,-2.5f,0.0f), glm::vec3(-2.5f,0.0f,0.0f)};
  model.setup(filepaths, meshPos);

  /* setup shaders */
  Shader shader("source/shaders/shader.vs", "source/shaders/shader.fs");
  Shader lightingShader("source/shaders/lighting_shader.vs", "source/shaders/lighting_shader.fs");

  glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);  //if changing this, change in mouse callback too
  glm::mat4 viewMatrix = view.getViewMatrix();

  glEnable(GL_DEPTH_TEST);

  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );


  while(!glfwWindowShouldClose(window))
  {

    if(view.listenToCallbacks(window) == 1)
    {
      model.selectObject(view.objPosition);
    }

    glClearColor(0.1f,0.1f,0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    viewMatrix = view.getViewMatrix();


    shader.use();
    shader.setMat4("projection", proj);
    shader.setMat4("view", viewMatrix);
    //shader.setVec3("objectColor", 0.7f, 0.5f, 1.0f);
    shader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
    shader.setVec3("lightPos",  0.0f, 0.0f ,5.0f);

    model.draw(shader, lightingShader);

    lightingShader.use();
    lightingShader.setMat4("projection", proj);
    lightingShader.setMat4("view", viewMatrix);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
}
