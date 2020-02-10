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
  std::string PLY_FILEPATH = "data/big_spider.ply";
  float *vertices;
  PlyParser::get_vertices(vertices, PLY_FILEPATH);
  int size = (sizeof(vertices)/sizeof(*vertices));

  normalize(vertices, size);
  
  Shader shader("source/shaders/shader.vs", "source/shaders/shader.fs");

   unsigned int indices[] = {};
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



    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    float angle = 0.0f;
  while(!glfwWindowShouldClose(window))
  {
    processInput(window);

    shader.use();
    glClearColor(0.0f,0.0f,0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.setFloat("vertexColor", 0.5f,0.0f,0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    angle = (angle + (float)1) ;
    trans = glm::rotate(trans, glm::radians(angle), glm::vec3(0.5f, 0.5f, 0.5f));
    //glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    //glm::mat4 trans = glm::mat4(1.0f);
    //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f,0.0f,0.1f));
    shader.setMat4("transform", trans);
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate( view, glm::vec3(0.0f, 0.0f, -0.5f));
    shader.setMat4("view", view);
    glBindVertexArray(VAO); 
    //glDrawArrays(GL_TRIANGLES, 0, 5);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    int length = (sizeof(indices)/sizeof(*indices));
    glDrawElements(GL_TRIANGLES,length, GL_UNSIGNED_INT, 0);
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
