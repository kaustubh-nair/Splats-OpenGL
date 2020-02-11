#include "../include/controller.h"
#include<cmath>

void normalize(float vertices[], int size)
{
  for(int i = 0; i < size; i+=3)
  {
    //x^2 + y^2 + z^2
    float v = pow(vertices[i],2) + pow(vertices[i+1],2) + pow(vertices[i+2],2);
    v = sqrt(v);
    vertices[i] = vertices[i]/v;
    vertices[i+1] = vertices[i+1]/v;
    vertices[i+2] = vertices[i+2]/v;
  }
}

void Controller::mainLoop( void )
{
  GLFWwindow* window = this->mainWindow;

  glewExperimental = GL_TRUE;
  glewInit();
  //Mesh mesh("data/f16.ply");
  Mesh mesh("data/big_spider.ply");
  
  Shader shader("source/shaders/shader.vs", "source/shaders/shader.fs");

  mesh.setup();

  glEnable(GL_DEPTH_TEST);

  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  float angle = 0.0f;
  while(!glfwWindowShouldClose(window))
  {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)800/(float)600, 0.1f, 100.0f);

    processInput(window);

    shader.use();

    glClearColor(0.0f,0.0f,0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -23.0f));
    model = glm::rotate(model, glm::radians(angle), glm::vec3(-0.1,1.0,0.2));

    shader.setFloat("vertexColor", 0.0f,0.5f,0.5f, 1.0f);
    shader.setMat4("projection", proj);
    shader.setMat4("view", view);
    shader.setMat4("model", model);

    mesh.draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
    angle = (angle + (float)1) ;
  }

  glfwTerminate();
}

void Controller::processInput(GLFWwindow* window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
