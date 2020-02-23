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
extern int num_segments;

class Mesh {
  public:
    int id;
    bool selected;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    /* splat related info */
    std::vector<InCircle> inCircles;
    std::vector<Vertex> inCircleVertices;
    std::vector<GLuint> fanStartingElements;

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
    void rotate(glm::vec2 direction);
    void changeSplatRadius(int direction);
    void addToInCircles(glm::vec3 normal, glm::vec3 vertex, bool center);


  private:
    unsigned int VAO, VBO, EBO;
    float splatMultipler;
    glm::vec3 position;

};


#endif
