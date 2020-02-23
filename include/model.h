#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "../include/mesh.h"
#include "../include/lighting.h"

class Model
{
  public:
    bool renderSplats;

    Model();
    void setup(std::vector<std::string> filepaths, std::vector<glm::vec3> locations);
    void draw(Shader shader, Shader lightingShader);
    void refresh();
    void changeSplatRadius(int direction);

    void unselect();
    void select(int direction);

    void translate(glm::vec2 direction);
    void scale(int direction);
    void rotate(glm::vec2 direction);

    void drawLighting( Shader shader);
  private:
    std::vector<Mesh> meshes;
    int selectedMesh;

};

#endif
