#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <string>
#include <vector>

#include "../include/ply_parser.h"
#include "../include/vertex.h"
#include "../include/in_circle.h"
#include "../include/shader.h"


extern int ID;

class Mesh {
  public:
    int id;
    bool selected;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    std::vector<InCircle> inCircles;
    std::vector<Vertex> inCircleVertices;

    Mesh(std::string filepath, glm::vec3 position);
    void setup();
    void draw(Shader shader);
    void setupSplats();
    void drawSplats(Shader shader);
    void computeInCirleVertices();
    glm::mat4 model;
    void scale(int direction);
    void translate(int direction);
    void rotate(int direction);

  private:
    unsigned int VAO, VBO, EBO;
    glm::vec3 position;

};


#endif
