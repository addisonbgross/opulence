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

#include "../container/obj_data.h"

class ObjLoader {
private:

public:
    ObjLoader();
    ~ObjLoader();
    obj_data import(std::string filePath);
    std::vector<mtl_data> importMtl(std::string fliePath);
    void checkHighMark(GLuint high, GLuint a, GLuint b, GLuint c);

    template<typename Type>
    void pushThree(std::vector<Type> &v, Type a, Type b, Type c);
};

#endif //OPULENCE_OBJLOADER_H
