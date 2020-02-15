#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <string>
#include <vector>

#include "../include/ply_parser.h"
#include "../include/vertex.h"
#include "../include/in_circle.h"
#include "../include/shader.h"


class Mesh {
  public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    std::vector<InCircle> inCircles;
    std::vector<Vertex> inCircleVertices;

    glm::vec3 position;

    Mesh(std::string filepath);
    void setup();
    void draw(float angle, Shader shader);
    void setupSplats();
    void drawSplats(float angle, Shader shader);
    void computeInCirleVertices();

  private:
    unsigned int VAO, VBO, EBO;

};


#endif
