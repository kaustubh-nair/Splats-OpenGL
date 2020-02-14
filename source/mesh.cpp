#include "../include/mesh.h"

void Mesh::draw_lighting( Shader shader)
{
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
  glm::mat4 model = glm::translate(glm::mat4(1.0f), lightPos);
  model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
  shader.setMat4("model", model);

  // render the cube
  glBindVertexArray(lightVAO);
  glDrawArrays(GL_TRIANGLES, 0, 1);
}
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

void Mesh::setupLighting()
{
  float lightVertices[] = {
    -0.1f, -0.1f, -0.1f
    };
  glGenVertexArrays(1, &lightVAO);
  glGenBuffers(1, &lightVBO);

  glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);

  glBindVertexArray(lightVAO);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
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
