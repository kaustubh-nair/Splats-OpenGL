#include "../include/controller.h"
#include<cmath>

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void Controller::mainLoop( void )
{
  glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
  glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
  GLFWwindow* window = this->mainWindow;

  glewExperimental = GL_TRUE;
  glewInit();

  float angle = 0.0f;
  
  Model model;
  Shader shader("source/shaders/shader.vs", "source/shaders/shader.fs");
  Shader lighting_shader("source/shaders/lighting_shader.vs", "source/shaders/lighting_shader.fs");

  float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    // first, configure the cube's VAO (and VBO)
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  unsigned int lightVAO;
  glGenVertexArrays(1, &lightVAO);
  glBindVertexArray(lightVAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // note that we update the lamp's position attribute's stride to reflect the updated buffer data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  std::vector<std::string> filepaths = {"data/f16.ply", "data/beethoven.ply"};
  std::vector<glm::vec3> locations = {glm::vec3(2.0,2.0,2.0), glm::vec3(-2.0,-2.0,-10.0)};

  model.setup(filepaths, locations);

  glEnable(GL_DEPTH_TEST);
  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

  glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)800/(float)600, 0.1f, 100.0f);
  glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

  shader.use();
  shader.setMat4("projection", proj);
  shader.setMat4("view", view);

  //unsigned int lightVAO;
  //glGenVertexArrays(1, &lightVAO);
  //glBindVertexArray(lightVAO);
  //glBindBuffer(GL_ARRAY_BUFFER, VBO);

  while(!glfwWindowShouldClose(window))
  {

    view = processInput(window);
    shader.setMat4("view", view);
    model.draw(angle,shader);

    glClearColor(0.0f,0.0f,0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    lighting_shader.use();
    lighting_shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    lighting_shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    lighting_shader.setVec3("lightPos", lightPos);

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
    lighting_shader.setMat4("projection", projection);
    lighting_shader.setMat4("view", view);

    // world transformation
    glm::mat4 lightmodel = glm::mat4(1.0f);
    lighting_shader.setMat4("model", lightmodel);

    // also draw the lamp object
    shader.use();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    lightmodel = glm::mat4(1.0f);
    lightmodel = glm::translate(lightmodel, lightPos);
    lightmodel = glm::scale(lightmodel, glm::vec3(0.2f)); // a smaller cube
    shader.setMat4("model", lightmodel);

    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);




    glfwSwapBuffers(window);
    glfwPollEvents();
    angle += 1.0;
  }
  glfwTerminate();
}

glm::mat4 Controller::processInput(GLFWwindow* window)
{
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
   const float cameraSpeed = 0.5f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
  return view;
}
