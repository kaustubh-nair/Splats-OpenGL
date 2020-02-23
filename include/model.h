#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "../include/mesh.h"
#include "../include/lighting.h"
#include "../include/fast_trackball.h"

class Model
{
  public:
    Model();
    void draw_lighting( Shader shader);
    void draw(Shader shader, Shader lightingShader);
    void setup(std::vector<std::string> filepaths, std::vector<glm::vec3> locations);
    void refresh();

    void unselect();
    void select(int direction);
    void translate(glm::vec2 direction);
    void scale(int direction);
    void rotate(Trackball trackball, glm::vec2 direction);
    void changeSplatRadius(int direction);

    bool renderSplats;
  private:
    std::vector<Mesh> meshes;
    int selectedMesh;

};

#endif
