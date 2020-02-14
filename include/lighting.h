#ifndef LIGHTING_H
#define LIGHTING_H

#include <GL/glew.h>
#include <string>
#include <vector>

#include "../include/shader.h"


class Lighting {
  public:
    glm::vec3 position;
    void setup();
    void draw(Shader shader);
  private:
    unsigned int VAO, VBO;

};


#endif
