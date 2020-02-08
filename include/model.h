#ifndef MODEL_H
#define MODEL_H

#include<bits/stdc++.h>
#include<glm/glm.hpp>
#include<string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "../include/shader.h"

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
};

struct Texture {
  unsigned int id;
  std::string type;
  std::string path;
};

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Mesh {
  public: 
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader shader);


  private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();


};
class Model
{
    public:
        /*  Functions   */
        Model(char *path)
        {
            loadModel(path);
        }
        void Draw(Shader shader);
    private:
        /*  Model Data  */
        std::vector<Mesh> meshes;
        std::string directory;
        /*  Functions   */
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                             std::string typeName);
};
#endif
