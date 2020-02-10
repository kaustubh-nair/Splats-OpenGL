#ifndef PLY_PARSER_H
#define PLY_PARSER_H


#include <iostream>
#include <fstream>
#include <string>

#include "../include/definitions.h"

class PlyParser
{
  public:

    static void get_vertices(float *vertices, std::string filepath)
    {
      std::ifstream ply_file;
      ply_file.open(filepath, std::ios::in);
      std::string line;
      if(ply_file.is_open())
      {
        std::string head_position = "header";
        int num_vertices = 0;
        int num_faces = 0;
        std::vector<std::string> split_line;

        while (getline(ply_file, line))
        {
          split(line, split_line, ' ');
          if(head_position.compare("header"))
          {
            if(line.compare("end_header"))
              head_position = "vertices";
            else if(split_line.at(0).compare("element"))
            {
              //save num vertices and face
              if(split_line.at(1).compare("vertex"))
                num_vertices = (int)split_line.at(2);
              else if(split_line.at(1).compare("face"))
                num_faces = (int)split_line.at(2);
            }
          }
          else if(head_position.compare("vertices"))
          {
          }
          else if(head_position.compare("indices"))
          {
          }
        }
      }
      else
      {
        print("Could not open file " + filepath);
      }

    }
    static float *get_indices(std::string filepath)
    {

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
