#include "../include/mesh.h"
#include<cmath>

int ID = 1;

Mesh::Mesh(std::string filepath, glm::vec3 position)
{
  id = ID;
  selected = false;
  ID++;
  PlyParser parser;
  parser.parse(filepath, vertices, indices); 
  position = position;
  inCircles = parser.inCircles;
  model = glm::translate(glm::mat4(1.0f), position);
}


void Mesh::translate(int direction)
{
  if(direction == UP)
    model = glm::translate(model, glm::vec3(0.0f, 0.2f,0.0f));
  else if(direction == DOWN)
    model = glm::translate(model, glm::vec3(0.0f, -0.2f,0.0f));
  else if(direction == RIGHT)
    model = glm::translate(model, glm::vec3(0.2f, 0.0f,0.0f));
  else if(direction == LEFT)
    model = glm::translate(model, glm::vec3(-0.2f, 0.0f,0.0f));
}


void Mesh::rotate(int direction)
{
  if(direction == CLOCKWISE)
    model = glm::scale(model, glm::vec3(1.1,1.1,1.1));
  else if(direction == ANTICLOCKWISE)
    model = glm::scale(model, glm::vec3(0.9,0.9,0.9));
}


void Mesh::scale(int direction)
{
  if(direction == UP)
    model = glm::scale(model, glm::vec3(1.1,1.1,1.1));
  else if(direction == DOWN)
    model = glm::scale(model, glm::vec3(0.9,0.9,0.9));
}


void Mesh::setupSplats()
{
  computeInCirleVertices();

  glGenVertexArrays(1 ,&VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, inCircleVertices.size() * sizeof(Vertex), &inCircleVertices[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
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


float angle = 0.0f;
void Mesh::drawSplats(Shader shader)
{
  angle++;
  shader.setVec3("vertexColor", 0.0f,0.1f,0.1f);
  shader.setMat4("model", model);
  //model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f,1.0f,0.0f));
  //model = glm::scale(model, glm::vec3(1.5,1.5,1.5));
  glBindVertexArray(VAO); 
  glDrawArrays(GL_TRIANGLES, 0, inCircleVertices.size());
}


void Mesh::draw(Shader shader)
{
  shader.setVec3("vertexColor", 0.0f,0.1f,0.1f);
  shader.setMat4("model", model);

  glBindVertexArray(VAO); 
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}


void Mesh::computeInCirleVertices()
{
  std::vector<InCircle>::iterator inCircle;

  int num_segments = 6;

  Vertex v;
  for(inCircle = inCircles.begin(); inCircle < inCircles.end(); inCircle++)
  {
    float radius = 0.1 * inCircle->radius;
    glm::vec3 v1 = inCircle->center;
    glm::vec3 v2 = v1 + (radius * normalize(glm::vec3(v.normal.z, 0, - v.normal.x)));
    v.position = v1;
    v.normal = inCircle->normal;
    inCircleVertices.push_back(v);

    v.position = v2;
    inCircleVertices.push_back(v);
    v.position = v1;

    /*
    float angle = 360.0f/num_segments;
    for(int i = 1; i < num_segments; i++)
    {
      glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(angle*i), inCircle->normal);
      glm::vec3 v3 = glm::vec3(rotationMat * glm::vec4(glm::normalize(v2-v1),1.0f)) + v1;
      v.position = v3;
      inCircleVertices.push_back(v);
    }*/
  }
}
