#ifndef OPULENCE_SHADERLOADER_H
#define OPULENCE_SHADERLOADER_H

// glew
#include <GL/glew.h>

// general
#include <fstream>
#include <vector>
#include <cstring>
#include <iostream>

/**
 * ShaderLoader - imports GLSL shader programs
 */
class ShaderLoader {
public:
    std::string readFile(const char *filePath);
    GLuint loadShader(const char *shaderPath, GLuint program);
};

#endif
