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

void Model::draw(Shader shader, Shader lightingShader)
{
  std::vector<Mesh>::iterator mesh;

  for (mesh = meshes.begin(); mesh < meshes.end(); mesh++)
  {
    (*mesh).draw(shader);
  }
  Lighting lighting;
  lighting.draw(lightingShader);
}

void Model::selectObject(glm::vec3 position)
{
  std::vector<Mesh>::iterator mesh;
  std::vector<int>::iterator id;

  std::vector<int> minIds;
  float minDistance = 100.0f;
  int minId;

  for (mesh = meshes.begin(); mesh < meshes.end(); mesh++)
  {
    float distance;
    glm::vec3 objPos = glm::normalize(mesh->position);
    distance = glm::distance(glm::vec2(objPos.x, objPos.y), glm::vec2(position.x, position.y));
    print(distance);

    if(distance < 0.6f)
      minIds.push_back(mesh->id);

    minId = mesh->id;
  }

  if(minIds.size() > 1)
  {
    for(mesh = meshes.begin(); mesh < meshes.end(); mesh++)
    {
      for(id = minIds.begin(); id < minIds.end(); id++)
      {
        if(mesh->id == *id)
        {
          if(mesh->position.z < minDistance)
          {
            minDistance = mesh->position.z;
            minId = *id;
          }
        }
      }

    }
  }
  else
    minId = minIds.at(0);
  for(mesh = meshes.begin(); mesh < meshes.end(); mesh++)
  {
    if(mesh->id == minId)
    {
      mesh->selected = true;
      break;
    }
  }
}
