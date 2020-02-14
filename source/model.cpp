#include "../include/model.h"

void Model::draw_lighting( Shader shader)
{
  meshes[0].draw_lighting(shader);
}
void Model::setup(std::vector<std::string> filepaths, std::vector<glm::vec3> locations)
{
  std::vector<std::string>::iterator filepath;
  std::vector<glm::vec3>::iterator location = locations.begin();

  for (filepath = filepaths.begin(); filepath < filepaths.end(); filepath++)
  {
    Mesh mesh(*filepath);
    mesh.location = *location;
    mesh.setup();
    meshes.push_back(mesh);

    location++;
  }
}

void Model::draw(float angle, Shader shader)
{
  std::vector<Mesh>::iterator mesh;

  for (mesh = meshes.begin(); mesh < meshes.end(); mesh++)
  {
    (*mesh).draw(angle,shader);
  }
}

