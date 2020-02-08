#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include<glm/glm.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class Shader
{
  public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value1, float value2, float value3, float value4) const;
    void setFloat1(const std::string &name,unsigned int value1) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

};
#endif
