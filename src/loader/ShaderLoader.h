#ifndef OPULENCE_SHADERLOADER_H
#define OPULENCE_SHADERLOADER_H

// glew
#define GLEW_STATIC
#include <GL/glew.h>

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
    std::string readFile(const char *filePath);                 // read in GLSL file
    GLuint loadShader(const char *shaderPath, GLuint program);  // compile and attach shader
};

#endif
