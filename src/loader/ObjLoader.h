#ifndef OPULENCE_OBJLOADER_H
#define OPULENCE_OBJLOADER_H

// general
#include <fstream>
#include <vector>

// glm
#include <glm/glm.hpp>

// glew
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #define GLEW_STATIC
    #include "../service/glew/glew.h"
#else
    #include "../service/glew/glew.h"
#endif

// gl
#include <GL/gl.h>

// opulence
#include "../container/obj_data.h"
#include "../container/mtl_data.h"

/**
 * ObjLoader - imports Wavefront Obj files (https://en.wikipedia.org/wiki/Wavefront_.obj_file)
 *             and loads the contents into an obj_data container that also holds many mtl_data
 *             containers. Currently, only models exported from Blender are useable
 */
class ObjLoader {
public:
    ObjLoader();
    ~ObjLoader();
    obj_data import(std::string filePath);                           // import vertex and material data
    std::vector<mtl_data> importMtl(std::string fliePath);           // import each material used in model

    template<typename Type>
    void checkHighMark(Type &high, Type a, Type b, Type c);          // check if a | b | c are higher than whatever
    template<typename Type>
    void pushThree(std::vector<Type> &v, Type a, Type b, Type c);    // adds 3 of whatever to a vector of whatever
};

#endif
