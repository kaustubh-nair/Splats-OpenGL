#include "../include/mesh.h"

Mesh::Mesh(std::string filepath)
{
  PlyParser::parse(filepath, vertices, indices);
}

void Mesh::setup()
{
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Mesh::draw(float angle, Shader shader)
{
  glm::mat4 model = glm::translate(glm::mat4(1.0f), location);
  model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0,1.0,0.0));
  shader.setVec3("vertexColor", 0.0f,0.1f,0.1f);
  shader.setMat4("model", model);
  //shader.setVec3("lightPos", lightPos);

  glBindVertexArray(VAO); 
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
