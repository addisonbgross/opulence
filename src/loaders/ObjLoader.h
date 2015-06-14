#ifndef OPULENCE_OBJLOADER_H
#define OPULENCE_OBJLOADER_H

#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <GL/gl.h>

struct obj_data {
    std::vector<GLfloat> position;
    std::vector<GLfloat> normal;
    std::vector<GLfloat> colour;
    std::vector<GLuint>  positionIndex;
    std::vector<GLuint>  uvIndex;
    std::vector<GLuint>  normalIndex;
};

struct mtl_data {
    std::string name;
    GLfloat diffuse[3];
    GLfloat specular[3];
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
