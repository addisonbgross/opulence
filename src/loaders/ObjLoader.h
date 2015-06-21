#ifndef OPULENCE_OBJLOADER_H
#define OPULENCE_OBJLOADER_H

#include <fstream>
#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <GL/gl.h>

struct obj_data {
    std::vector<GLfloat> position;
    std::vector<GLfloat> normal;
    std::vector<GLfloat> diffuse;
    std::vector<GLfloat> specular;
    std::vector<GLuint>  positionIndex;
    std::vector<GLuint>  uvIndex;
    std::vector<GLuint>  normalIndex;
    std::vector<GLuint>  colourIndex;
};

struct mtl_data {
    std::string name;
    std::vector<GLuint> faces;
    glm::vec4 diffuse;
    glm::vec4 specular;
};

class ObjLoader
{
private:

public:
    ObjLoader();
    obj_data import(std::string filePath);
    std::vector<mtl_data> importMtl(std::string fliePath);
};

#endif //OPULENCE_OBJLOADER_H
