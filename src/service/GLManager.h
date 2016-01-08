#ifndef OPULENCE_GLMANAGER_H
#define OPULENCE_GLMANAGER_H

// general
#include <SDL.h>

// opulence
#include "../loader/ShaderLoader.h"
#include "../service/OsType.h"

/**
 * GLManager - Initializes and controls SDL and OpenGL capabilites
 */
class GLManager {
private:
    GLuint programID;                     // current OpenGL instance id
    GLuint vertexShader, fragmentShader;  // references to loaded shaders
    GLuint VAO;                           // Vertex Array Object
    SDL_Window *window;                   // general window management access
    SDL_Surface *surface;                 // holds information about FBO
    GLfloat screenWidth, screenHeight;    // current resolution of game window

public:
    bool initGL();                             // initialize OpenGL
    bool initSDL();                            // initialize SDL
    void shutDown();                           // free up OpenGL/SDL resources

    // get
    GLuint getID();
    GLuint getVertexShader();
    GLuint getFragmentShader();
    GLuint getVAO();
    GLfloat getScreenWidth();
    GLfloat getScreenHeight();
    SDL_Window *getWindow();
    SDL_Surface *getSurface();

    // set
    void setScreenSize(GLfloat w, GLfloat h);  // set resolution of game window
};

#endif
