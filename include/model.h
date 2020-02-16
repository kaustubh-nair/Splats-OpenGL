#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "../include/mesh.h"
#include "../include/lighting.h"

class Model
{
  public:
    Model();
    void draw_lighting( Shader shader);
    void draw(Shader shader, Shader lightingShader);
    void setup(std::vector<std::string> filepaths, std::vector<glm::vec3> locations);

    void unselect();
    void select(int direction);
    void translate(int direction);
    void scale(int direction);
    void rotate(int direction);
  private:
    std::vector<Mesh> meshes;
    int selectedMesh;

};

#endif
