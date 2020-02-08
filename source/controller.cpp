#include "../include/controller.h"

void Controller::mainLoop( void )
{
  GLFWwindow* window = this->mainWindow;

  glewExperimental = GL_TRUE;
  glewInit();
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };  
  
  Shader shader("source/shaders/shader.vs", "source/shaders/shader.fs");

   unsigned int indices[] = {  
        0, 1, 3,  
        1, 2, 3   
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW)    ;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);


  while(!glfwWindowShouldClose(window))
  {
    processInput(window);
    float random = rand() % 3;

    float red = 0.5f;
    float green = 0.5f;
    float blue = 0.5f;
    if(random == 0)
      red = 1.0f;
    else if(random == 1)
      green = 1.0f;
    else 
      blue = 1.0f;

    shader.use();
    glClearColor(green,red,green, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.setFloat("vertexColor", red,green,blue, 1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(red, green, blue));
    shader.setMat4("transform", trans);
    glBindVertexArray(VAO); 
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
}

void Controller::processInput(GLFWwindow* window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
