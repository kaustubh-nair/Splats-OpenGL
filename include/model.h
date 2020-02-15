#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "../include/mesh.h"
#include "../include/lighting.h"

class Model
{
  public:

    void draw_lighting( Shader shader);
    void draw(Shader shader, Shader lightingShader);
    void setup(std::vector<std::string> filepaths, std::vector<glm::vec3> locations);
  private:
    std::vector<Mesh> meshes;

};

#endif
