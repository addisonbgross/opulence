#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>

#include "ShaderLoader.h"

std::string readFile(const char *filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}


bool loadShader(const char *shaderPath, GLuint program) {
    GLchar fileExtension = shaderPath[strlen(shaderPath) - 4];

    //Create vertex shader
    GLuint shader = (fileExtension == 'v') ? glCreateShader(GL_VERTEX_SHADER) :
                                             glCreateShader(GL_FRAGMENT_SHADER);

    //Get vertex source
    const GLchar *shaderSource[] = {readFile(shaderPath).c_str()};

    //Set vertex source
    glShaderSource(shader, 1, shaderSource, NULL);

    //Compile vertex source
    glCompileShader(shader);

    //Check vertex shader for errors
    GLint isCompiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled != GL_TRUE) {
        printf("Unable to compile shader from %s!\n", shaderPath);
        return false;
    } else {
        glAttachShader(program, shader);
        return true;
    }
}