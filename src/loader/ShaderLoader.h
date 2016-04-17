#ifndef OPULENCE_SHADERLOADER_H
#define OPULENCE_SHADERLOADER_H

// glew
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #define GLEW_STATIC
    #include "../service/glew/glew.h"
#else
    #include <GL/glew.h>
#endif

// general
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>

/**
 * ShaderLoader - imports GLSL shader programs
 */
class ShaderLoader {
public:
    std::string readFile(std::string filePath);                 // read in GLSL file
    GLuint loadShader(std::string shaderPath, GLuint program);  // compile and attach shader
};

#endif
