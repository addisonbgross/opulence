#ifndef OPULENCE_OBJLOADER_H
#define OPULENCE_OBJLOADER_H

#include <fstream>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <GL/gl.h>

struct obj_data {
    std::vector<GLfloat> position;
    std::vector<GLfloat> normal;
    std::vector<GLfloat> colour;
    std::vector<GLuint>  index;
};

class ObjLoader
{
private:

public:
    ObjLoader();
    obj_data import(const char * filePath);
};

#endif //OPULENCE_OBJLOADER_H
