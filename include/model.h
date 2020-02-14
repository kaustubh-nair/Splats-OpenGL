#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "../include/mesh.h"

class Model
{
  public:
    void draw(float angle, Shader shader);
    void setup(std::vector<std::string> filepaths, std::vector<glm::vec3> locations);
  private:
    std::vector<Mesh> meshes;

};

#endif
