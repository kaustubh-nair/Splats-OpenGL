#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <string>
#include <vector>

#include "../include/vertex.h"
#include "../include/shader.h"


class Lighting {
  public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    glm::vec3 location;
    Mesh(std::string filepath);
    static void setup();
    static void draw(float angle, Shader shader);
  private:
    unsigned int VAO, VBO;

};


#endif
