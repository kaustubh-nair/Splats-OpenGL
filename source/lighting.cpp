static void Lighting::draw(Shader shader)
{
  glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
  glm::mat4 model = glm::translate(glm::mat4(1.0f), lightPos);
  model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
  shader.setMat4("model", model);

  // render the cube
  glBindVertexArray(lightVAO);
  glDrawArrays(GL_TRIANGLES, 0, 1);
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

