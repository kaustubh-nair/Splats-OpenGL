#include "../include/mesh.h"
#include<cmath>

Mesh::Mesh(std::string filepath)
{
  PlyParser parser;
  parser.parse(filepath, vertices, indices); 

  faceNormals = parser.faceNormals;
  inCenters = parser.inCenters;
  inRadii = parser.inRadii;
}

void Mesh::setup()
{
  std::vector<glm::vec3>::iterator faceNormal;
  std::vector<glm::vec3>::iterator inCenter = inCenters.begin();
  std::vector<float>::iterator inRadius = inRadii.begin();

  for(faceNormal = faceNormals.begin(); faceNormal < faceNormals.end(); faceNormal++)
  {
    //compute vertices
    //

    glm::vec3 v1 = *inCenter;
    glm::vec3 v2 = v1 + ((*inRadius) * normalize(glm::vec3(faceNormal->z, 0, - faceNormal->x)));
    if(std::isnan(v1.x))
      continue;
    if(std::isnan(v2.x))
      continue;

    glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(60.0f), *faceNormal);
    glm::vec3 v3 = glm::vec3(rotationMat * glm::vec4(glm::normalize(v2-v1),1.0f)) + v1;

    rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(120.0f), *faceNormal);
    glm::vec3 v4 = glm::vec3(rotationMat * glm::vec4(glm::normalize(v2-v1),1.0f)) + v1;
    if(std::isnan(v3.x))
      continue;

    rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), *faceNormal);
    glm::vec3 v5 = glm::vec3(rotationMat * glm::vec4(glm::normalize(v2-v1),1.0f)) + v1;

    rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(240.0f), *faceNormal);
    glm::vec3 v6 = glm::vec3(rotationMat * glm::vec4(glm::normalize(v2-v1),1.0f)) + v1;

    rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(300.0f), *faceNormal);
    glm::vec3 v7 = glm::vec3(rotationMat * glm::vec4(glm::normalize(v2-v1),1.0f)) + v1;

    inCircleVertices.insert(inCircleVertices.end(), {
        v1.x,  v1.y,  v1.z,          
        faceNormal->x,faceNormal->y,faceNormal->z,
        v2.x,  v2.y,  v2.z,          
        faceNormal->x,faceNormal->y,faceNormal->z,
        v3.x,  v3.y,  v3.z,          
        faceNormal->x,faceNormal->y,faceNormal->z,
        v1.x,  v1.y,  v1.z,          
        faceNormal->x,faceNormal->y,faceNormal->z,
        v3.x,  v3.y,  v3.z,          
        faceNormal->x,faceNormal->y,faceNormal->z,
        v4.x,  v4.y,  v4.z,          
        faceNormal->x,faceNormal->y,faceNormal->z,
        v1.x,  v1.y,  v1.z,          
        faceNormal->x,faceNormal->y,faceNormal->z,
        v4.x,  v4.y,  v4.z,          
        faceNormal->x,faceNormal->y,faceNormal->z,
        v5.x,  v5.y,  v5.z,          
        faceNormal->x,faceNormal->y,faceNormal->z,
        v1.x,  v1.y,  v1.z,          
        faceNormal->x,faceNormal->y,faceNormal->z,
        v5.x,  v5.y,  v5.z,          
        faceNormal->x,faceNormal->y,faceNormal->z,
        v6.x,  v6.y,  v6.z,          
        faceNormal->x,faceNormal->y,faceNormal->z,
        v1.x,  v1.y,  v1.z,          
        faceNormal->x,faceNormal->y,faceNormal->z,
        v6.x,  v6.y,  v6.z,          
        faceNormal->x,faceNormal->y,faceNormal->z,
        v7.x,  v7.y,  v7.z,          
        faceNormal->x,faceNormal->y,faceNormal->z,
        v1.x,  v1.y,  v1.z,          
        faceNormal->x,faceNormal->y,faceNormal->z,
        v7.x,  v7.y,  v7.z,          
        faceNormal->x,faceNormal->y,faceNormal->z,
        v2.x,  v2.y,  v2.z          ,
        faceNormal->x,faceNormal->y,faceNormal->z
        });

    inRadius++;
    inCenter++;
  }

  unsigned int normalVBO;
  glGenVertexArrays(1 ,&VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, inCircleVertices.size() * sizeof(float), &inCircleVertices[0], GL_STATIC_DRAW);


  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  glBindVertexArray(0);

  /*
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
  */


}

void Mesh::draw(float angle, Shader shader)
{
  glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
  model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0,1.0,0.0));
  shader.setVec3("vertexColor", 0.0f,0.1f,0.1f);
  shader.setMat4("model", model);
  //shader.setVec3("lightPos", lightPos);

  /*
  glBindVertexArray(VAO); 
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  */
  glBindVertexArray(VAO); 
  glDrawArrays(GL_TRIANGLES, 0, inCircleVertices.size()/3 );
}
