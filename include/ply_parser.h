#ifndef PLY_PARSER_H
#define PLY_PARSER_H

//careful: no multiple declarations for glm allowed
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../include/definitions.h"
#include "../include/vertex.h"

class PlyParser
{
  public:
    // store vertices and indices
    static void parse(std::string filepath, std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
    {
      std::ifstream ply_file;
      ply_file.open(filepath, std::ios::in);
      std::string line;
      int i,j,num_vertices,num_faces;
      float x,y,z;
      if(ply_file.is_open())
      {
        std::string head_position = "header";
        std::vector<std::string> split_line;

        while (getline(ply_file, line))
        {
          split(line, split_line, ' ');
          if(!head_position.compare("header"))
          {
            if(split_line[0].compare("end_header\r") == 0 || split_line[0].compare("end_header") == 0)
              head_position = "vertices";
            else if(!split_line[0].compare("element"))
            {
              //save num vertices and face
              if(!split_line[1].compare("vertex"))
              {
                num_vertices = std::stoi(split_line[2]);
                i = num_vertices;
              }
              else if(!split_line[1].compare("face"))
              {
                num_faces = std::stoi(split_line[2]);
                j = num_faces;
              }
            }
          }
          else if(!head_position.compare("vertices"))
          {
            if(i == 1)
              head_position = "indices";

            split(line, split_line, ' ');
            x = std::atof(split_line[0].c_str()); // x
            y = std::atof(split_line[1].c_str()); // y
            z = std::atof(split_line[2].c_str()); // z

            Vertex vertex = {glm::vec3(x,y,z)};
            vertices.push_back(vertex);
            i--;
          }
          else if(!head_position.compare("indices"))
          {
            if(j == 1)
              head_position = "end";

            split(line, split_line, ' ');
            if(std::stoi(split_line[0]) != 3)
            {
              print("Face not triangular");
              continue;
            }
            indices.push_back(std::stoi(split_line[1].c_str()));
            indices.push_back(std::stoi(split_line[2].c_str()));
            indices.push_back(std::stoi(split_line[3].c_str()));

            j--;
          }
          else
          {
            print("Error parsing file");
            print("head position: " + head_position);
          }
        }
      }
      else
      {
        print("Could not open file " + filepath);
      }
    }

  private:
    // split string by spaces
    // https://stackoverflow.com/a/5888676
    static size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
    {
        size_t pos = txt.find( ch );
        size_t initialPos = 0;
        strs.clear();

        // Decompose statement
        while( pos != std::string::npos ) {
            strs.push_back( txt.substr( initialPos, pos - initialPos ) );
            initialPos = pos + 1;

            pos = txt.find( ch, initialPos );
        }

        // Add the last one
        strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

        return strs.size();
    }
};
#endif
