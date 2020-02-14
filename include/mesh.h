#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <string>
#include <vector>

#include "../include/ply_parser.h"
#include "../include/vertex.h"
#include "../include/shader.h"


class Mesh {
  public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    glm::vec3 position;

    Mesh(std::string filepath);
    void setup();
    void draw(float angle, Shader shader);

  private:
    unsigned int VAO, VBO, EBO;

};


#endif
