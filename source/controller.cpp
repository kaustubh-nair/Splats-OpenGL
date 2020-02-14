#include "../include/controller.h"
#include<cmath>


void Controller::mainLoop( void )
{
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
  GLFWwindow* window = this->mainWindow;

  glewExperimental = GL_TRUE;
  glewInit();

  float angle = 0.0f;
  
  Model model;
  Shader shader("source/shaders/shader.vs", "source/shaders/shader.fs");
  Shader lightingShader("source/shaders/lighting_shader.vs", "source/shaders/lighting_shader.fs");

  std::vector<std::string> filepaths = {"data/f16.ply", "data/beethoven.ply"};
  std::vector<glm::vec3> locations = {glm::vec3(2.0,2.0,2.0), glm::vec3(-2.0,-2.0,-10.0)};

  model.setup(filepaths, locations);

  glEnable(GL_DEPTH_TEST);
  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );



  while(!glfwWindowShouldClose(window))
  {
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)800/(float)600, 0.1f, 100.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,-20.0f));

    shader.use();
    shader.setMat4("projection", proj);
    shader.setMat4("view", view);
    shader.setVec3("objectColor", 0.8f, 0.07f, 0.7f);
    shader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
    shader.setVec3("lightPos",  lightPos);

    glClearColor(0.0f,0.0f,0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    model.draw(angle,shader);

    lightingShader.use();
    lightingShader.setMat4("projection", proj);
    lightingShader.setMat4("view", view);
    model.draw_lighting(lightingShader);

    glfwSwapBuffers(window);
    glfwPollEvents();
    angle += 1.0;
  }
  glfwTerminate();
}
