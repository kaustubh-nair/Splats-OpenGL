#include "../include/model.h"

Model::Model()
{
  selectedMesh = -1;
}
void Model::setup(std::vector<std::string> filepaths, std::vector<glm::vec3> meshPos)
{
  std::vector<std::string>::iterator filepath;
  std::vector<glm::vec3>::iterator position = meshPos.begin();

  for (filepath = filepaths.begin(); filepath < filepaths.end(); filepath++)
  {
    Mesh mesh(*filepath, *position);
    mesh.setupSplats();
    meshes.push_back(mesh);

    position++;
  }

}


void Model::draw(Shader shader, Shader lightingShader)
{
  std::vector<Mesh>::iterator mesh;

  for (mesh = meshes.begin(); mesh < meshes.end(); mesh++)
  {
    (*mesh).drawSplats(shader);
  }
  Lighting lighting;
  lighting.draw(lightingShader);
}


void Model::unselect()
{
  std::vector<Mesh>::iterator mesh;

  for (mesh = meshes.begin(); mesh < meshes.end(); mesh++)
  {
    if(mesh->id == selectedMesh)
    {
      mesh->selected = false;
      break;
    }
  }
  selectedMesh = -1;
}

void Model::select(int id)
{
  if(selectedMesh != -1)
    return;
  selectedMesh = id;

  std::vector<Mesh>::iterator mesh;
  for (mesh = meshes.begin(); mesh < meshes.end(); mesh++)
  {
    if(mesh->id == id)
    {
      mesh->selected = true;
      break;
    }
  }
}

void Model::translate(int direction)
{
  if(selectedMesh == -1)
    return;
  meshes[selectedMesh - 1].translate(direction);
}


void Model::scale(int direction)
{
  if(selectedMesh == -1)
    return;

  meshes[selectedMesh - 1].scale(direction);
}


void Model::rotate(int direction)
{
  if(selectedMesh == -1)
    return;
  meshes[selectedMesh - 1].rotate(direction);

}
//object selection code
/*
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
    glm::vec3 objPos = mesh->position/6.0f;
    distance = glm::distance(glm::vec2(objPos.x, objPos.y), glm::vec2(position.x, position.y));

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
      //print(mesh->id);
      break;
    }
  }
}
*/


