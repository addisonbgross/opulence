#include "ShaderLoader.h"

/**
 * readFile() - read in GLSL shader from flie path
 *
 * @params *filePath relative to opulence root folder
 * @return std::string the entire GLSL file as a string
 */
std::string ShaderLoader::readFile(const char *filePath) {
    // open shader file
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    // read in shader
    std::string shaderString;
    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        shaderString.append(line + "\n");
    }

    fileStream.close();

    return shaderString;
}

/**
 * loadShader() - parse a GLSL shader and attach it to OpenGL context
 *
 * @return GLuint handle for GLSL shader in video card
 */
GLuint ShaderLoader::loadShader(const char *shaderPath, GLuint program) {
    GLchar fileExtension = shaderPath[strlen(shaderPath) - 4];

    // create appropriate shader handle
    GLuint shader;
    if (fileExtension == 'v') {
        shader = glCreateShader(GL_VERTEX_SHADER);
    } else if (fileExtension == 'f') {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    } else if (fileExtension == 'g') {
        shader = glCreateShader(GL_GEOMETRY_SHADER);
    }

    //Get vertex source
    const GLchar *shaderSource = { readFile(shaderPath).c_str() };

    //Set vertex source
    glShaderSource(shader, 1, &shaderSource, NULL);

    //Compile vertex source
    glCompileShader(shader);

    //Check vertex shader for errors
    GLint isCompiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled != GL_TRUE) {
        return 0;
    } else {
        glAttachShader(program, shader);
        return shader;
    }
}