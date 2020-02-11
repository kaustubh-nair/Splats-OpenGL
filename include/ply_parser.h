#ifndef PLY_PARSER_H
#define PLY_PARSER_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../include/definitions.h"

class PlyParser
{
  public:
    std::string filepath;
    float *vertices;
    float *indices;


    // save vertices and indices
    PlyParser(std::string filepath)
    {
      this->filepath = filepath;

      std::ifstream ply_file;
      ply_file.open(filepath, std::ios::in);
      std::string line;
      int i,j;
      if(ply_file.is_open())
      {
        std::string head_position = "header";
        int num_vertices = 0;
        int num_faces = 0;
        std::vector<std::string> split_line;

        while (getline(ply_file, line))
        {
          split(line, split_line, ' ');
          if(!head_position.compare("header"))
          {
            if(!split_line[0].compare("end_header\r"))
              head_position = "vertices";
            else if(!split_line[0].compare("element"))
            {
              //save num vertices and face
              if(!split_line[1].compare("vertex"))
              {
                num_vertices = std::stoi(split_line[2]);
                i = num_vertices;
                vertices = new float [3 * num_vertices];  //3 - number of components of vertex
              }
              else if(!split_line[1].compare("face"))
              {
                num_faces = std::stoi(split_line[2]);
                j = num_faces;
                indices = new float [3 * num_faces];  // 3 - triangular faces
              }
            }
          }
          else if(!head_position.compare("vertices"))
          {
            if(i == 1)
              head_position = "indices";

            split(line, split_line, ' ');
            vertices[(3*num_vertices) - (3*i)] = std::atof(split_line[0].c_str()); // x
            vertices[(3*num_vertices) - ((3*i) + 1)] = std::atof(split_line[1].c_str()); // y
            vertices[(3*num_vertices) - ((3*i) + 2)] = std::atof(split_line[2].c_str()); // z
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
            indices[(3*num_faces) - (3*i)] = std::stoi(split_line[1].c_str()); // x
            indices[(3*num_faces) - ((3*i) + 1)] = std::stoi(split_line[2].c_str()); // y
            indices[(3*num_faces) - ((3*i) + 2)] = std::stoi(split_line[3].c_str()); // z
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

      print(indices[0]);
      print(indices[10]);
      print(indices[100]);
      print(indices[4000]);

    }
  private:
    // split string by spaces
    // https://stackoverflow.com/a/5888676
    size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
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
