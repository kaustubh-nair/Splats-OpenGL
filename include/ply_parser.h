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
#include "../include/in_circle.h"

class PlyParser
{
  public:
    std::vector<InCircle> inCircles;

    // store vertices and indices
    void parse(std::string filepath, std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
    {
      std::ifstream ply_file;
      ply_file.open(filepath, std::ios::in);
      std::string line;
      int i,j,num_vertices,num_faces;
      float x,y,z;
      float max = -10000000.0;
      float min = 1000000000.0;
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

            min = std::min(min, std::min(x, std::min(y, z)));
            max = std::max(max, std::max(x, std::max(y, z)));

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
            /* store indices */
            int v1 = std::stoi(split_line[1].c_str());
            int v2 = std::stoi(split_line[2].c_str());
            int v3 = std::stoi(split_line[3].c_str());

            Vertex a = vertices.at(v1);
            Vertex b = vertices.at(v2);
            Vertex c = vertices.at(v3);

            glm::vec3 normal = glm::normalize( glm::cross(b.position - a.position, c.position - a.position) );


            a.face_normals.push_back(normal);
            b.face_normals.push_back(normal);
            c.face_normals.push_back(normal);

            vertices.at(v1) = a;
            vertices.at(v2) = b;
            vertices.at(v3) = c;

            indices.push_back(v1);
            indices.push_back(v2);
            indices.push_back(v3);

            compute_incircle(normal,a,b,c);

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
      normalize_vertices(vertices, min, max);
      compute_vertex_normals(vertices);
    }

    /* scale vertices to [-1,1] */
    void normalize_vertices(std::vector<Vertex> &vertices, float min, float max)
    {
      std::vector<Vertex>::iterator vertex;
      float x,y,z,d;

      for(vertex = vertices.begin(); vertex < vertices.end(); vertex++)
      {
        d = max-min;
        x = vertex->position.x;
        y = vertex->position.y;
        z = vertex->position.z;

        x = (x-min)/d - 0.5;
        y = (y-min)/d - 0.5;
        z = (z-min)/d - 0.5;
        vertex->position = glm::vec3(2*x, 2*y, 2*z);
      }
    }

    void compute_vertex_normals(std::vector<Vertex> &vertices)
    {
      std::vector<Vertex>::iterator vertex;
      std::vector<glm::vec3>::iterator normal;

      for(vertex = vertices.begin(); vertex < vertices.end(); vertex++)
      {
        glm::vec3 vec_normal = glm::vec3(0.0, 0.0, 0.0);

        for(normal = vertex->face_normals.begin(); normal < vertex->face_normals.end(); normal++)
          vec_normal = vec_normal + *normal;

        vertex->normal = glm::normalize(vec_normal);
      }
    }


    void compute_incircle(glm::vec3 normal, Vertex a, Vertex b, Vertex c)
    {
      float area = 0.5 * glm::length( glm::cross(a.position - c.position, b.position - c.position) );

      float faceA = glm::length(b.position - c.position);
      float faceB = glm::length(a.position - c.position);
      float faceC = glm::length(a.position - b.position);

      float incenterX = (faceA*a.position.x) + (faceB * b.position.x) + (faceC * c.position.x);
      float incenterY = (faceA*a.position.y) + (faceB * b.position.y) + (faceC * c.position.y);
      float incenterZ = (faceA*a.position.z) + (faceB * b.position.z) + (faceC * c.position.z);

      glm::vec3 incenter = glm::vec3( incenterX, incenterY, incenterZ);
      incenter = incenter/(faceA + faceB + faceC);

      float semiPerimeter = 0.5 * (faceA + faceB + faceC);
      float inRadius = area/semiPerimeter;

      InCircle incircle;
      incircle.center = incenter;
      incircle.radius = inRadius;
      incircle.normal = normal;

      inCircles.push_back(incircle);
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
