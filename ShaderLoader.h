#ifndef OPULENCE_SHADERLOADER_H
#define OPULENCE_SHADERLOADER_H

#include <GL/glew.h>
#include <iostream>

std::string readFile(const char *filePath);
bool loadShader(const char *shaderPath, GLuint program);

#endif //OPULENCE_SHADERLOADER_H
