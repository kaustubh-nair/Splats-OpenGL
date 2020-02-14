#include "../include/controller.h"
#include<cmath>


void Controller::mainLoop( void )
{
  GLFWwindow* window = this->mainWindow;

  glewExperimental = GL_TRUE;
  glewInit();

  Model model;
  Shader shader("source/shaders/shader.vs", "source/shaders/shader.fs");
  Shader lightingShader("source/shaders/lighting_shader.vs", "source/shaders/lighting_shader.fs");

  std::vector<std::string> filepaths = { "data/beethoven.ply" };
  std::vector<glm::vec3> meshPos = {glm::vec3(0.0f,0.0f,0.0f)};
  //std::vector<std::string> filepaths = {"data/beethoven.ply", "data/shark.ply", "data/apple.ply" , "data/big_spider.ply"};
  //std::vector<glm::vec3> meshPos = {glm::vec3(-2.0,-2.0,-12.0), glm::vec3(5.0,0.0,-1.0), glm::vec3(5.0, -4.0, -1.0), glm::vec3(-5.0, 0.0, -1.0)};
  float angle = 0.0f;

  model.setup(filepaths, meshPos);

  glEnable(GL_DEPTH_TEST);
  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

  while(!glfwWindowShouldClose(window))
  {
    glClearColor(0.0f,0.0f,0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)800/(float)600, 0.1f, 100.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,-1.0f));

    shader.use();
    shader.setMat4("projection", proj);
    shader.setMat4("view", view);
    //shader.setVec3("objectColor", 0.7f, 0.3f, 1.0f);
    shader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
    shader.setVec3("lightPos",  0.0f, 0.0f ,0.0f);

    model.draw(angle, shader, lightingShader);

    lightingShader.use();
    lightingShader.setMat4("projection", proj);
    lightingShader.setMat4("view", view);

    glfwSwapBuffers(window);
    glfwPollEvents();
    angle += 1.0;
  }
  glfwTerminate();
}
