#include "../include/model.h"


void Model::setup(std::vector<std::string> filepaths, std::vector<glm::vec3> meshPos)
{
  std::vector<std::string>::iterator filepath;
  std::vector<glm::vec3>::iterator position = meshPos.begin();

  for (filepath = filepaths.begin(); filepath < filepaths.end(); filepath++)
  {
    Mesh mesh(*filepath);
    mesh.position = *position;
    mesh.setup();
    meshes.push_back(mesh);

    position++;
  }

}

void Model::draw(float angle, Shader shader, Shader lightingShader)
{
  std::vector<Mesh>::iterator mesh;

  for (mesh = meshes.begin(); mesh < meshes.end(); mesh++)
  {
    (*mesh).draw(angle,shader);
  }
  Lighting lighting;
  lighting.draw(lightingShader);
}
