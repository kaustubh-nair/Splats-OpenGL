#include "../include/lighting.h"



void Lighting::setup()
{
  float vertices[] = { 0.5f, 1.5f, 10.0f};
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, 3*sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(VAO);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
  glEnableVertexAttribArray(0);
}

void Lighting::draw(Shader shader)
{
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3( 2.5f, 2.5f, 10.0f ));
  shader.setMat4("model", model);

  // render the cube
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 1);
}
