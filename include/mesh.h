#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <string>
#include <vector>

#include "../include/ply_parser.h"
#include "../include/vertex.h"


class Mesh {
  public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Mesh(std::string filepath);
    void setup();
    void draw();

  private:
    unsigned int VAO, VBO, EBO;

};


#endif
