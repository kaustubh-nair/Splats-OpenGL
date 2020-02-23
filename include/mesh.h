#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <string>
#include <vector>

#include "../include/ply_parser.h"
#include "../include/vertex.h"
#include "../include/in_circle.h"
#include "../include/shader.h"
#include "../include/fast_trackball.h"



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
    glm::mat4 translationMatrix;
    glm::mat4 scalingMatrix;
    glm::mat4 rotationMatrix;
    void scale(int direction);
    void translate(glm::vec2 direction);
    void rotate(Trackball trackball, glm::vec2 direction);
    void changeSplatRadius(int direction);

  private:
    unsigned int VAO, VBO, EBO;
    float splatMultipler;
    glm::vec3 position;

};


#endif
