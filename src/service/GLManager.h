#ifndef OPULENCE_GLMANAGER_H
#define OPULENCE_GLMANAGER_H

#include <iostream>

#include <SDL.h>
#include <GL/glew.h>

#include "../loader/ShaderLoader.h"

class GLManager {
private:
    GLuint programID;
    GLuint vertexShader, fragmentShader;
    GLuint VAO;
    SDL_Window *window;

    GLfloat screenWidth, screenHeight;

    SDL_Window *gWindow = NULL; //The window we'll be rendering to
    SDL_GLContext gContext; //OpenGL context

public:
    bool initGL();
    bool initSDL();
    GLuint getID();
    GLuint getVertexShader();
    GLuint getFragmentShader();
    GLuint getVAO();
    SDL_Window *getWindow();

    void setScreenSize(GLfloat w, GLfloat h);
    void shutDown();
};


#endif //OPULENCE_GLMANAGER_H
