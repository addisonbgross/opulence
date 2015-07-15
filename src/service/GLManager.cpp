//
// Created by champ on 14/07/15.
//

#include "GLManager.h"

bool GLManager::initGL()
{
    // success flag
    bool success = true;

    // generate program
    programID = glCreateProgram();

    // enable z-buffer face culling
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_FLAT);

    // enable vsync rate
    if (SDL_GL_SetSwapInterval(1) < 0)
        std::cout << "Swap Interval could not be set!" << std::endl;

    // vertex & fragment
    vertexShader   = loadShader("/home/champ/Git/crows/opulence/shaders/phongAttenuation.vert", programID);
    fragmentShader = loadShader("/home/champ/Git/crows/opulence/shaders/phongAttenuation.frag", programID);

    // TODO fix this mess
    int failCount = 0;
    while (vertexShader == 0) {
        ++failCount;
        std::cout << "Loading vertexShader failed!" << std::endl;
        vertexShader = loadShader("/home/champ/Git/crows/opulence/shaders/phongAttenuation.vert", programID);

        if (failCount == 10) {
            failCount = 0;
            break;
        }
    }
    while (fragmentShader == 0) {
        ++failCount;
        std::cout << "Loading fragmentShader failed!" << std::endl;
        fragmentShader = loadShader("/home/champ/Git/crows/opulence/shaders/phongAttenuation.frag", programID);
        if (failCount == 10) {
            failCount = 0;
            break;
        }
    }

    // create VAO
    glGenVertexArrays(1, &VAO);

    glLinkProgram(programID);

    //Initialize clear color
    glClearColor(0.0, 0.0, 0.0, 1.0f);

    return success;
}

bool GLManager::initSDL()
{
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;

    //Use OpenGL 3.3 core
    } else {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

        glEnable(GL_MULTISAMPLE);

        //Create window
        window = SDL_CreateWindow("opulence v1.0",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   screenWidth, screenHeight,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN); // full screen --> SDL_WINDOW_FULLSCREEN

        SDL_GLContext glcontext(SDL_GL_CreateContext(window));

        glewExperimental = GL_TRUE;
        GLenum glewError = glewInit();

        //Use Vsync
        if (SDL_GL_SetSwapInterval(1) < 0) {
            printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
        }

    }

        return success;
}

GLuint GLManager::getID()
{
    return programID;
}

GLuint GLManager::getVertexShader()
{
    return vertexShader;
}

GLuint GLManager::getFragmentShader()
{
    return fragmentShader;
}

GLuint GLManager::getVAO()
{
    return VAO;
}

SDL_Window *GLManager::getWindow()
{
    return window;
}

void GLManager::setScreenSize(GLfloat w, GLfloat h)
{
    screenWidth = w;
    screenHeight = h;
}

void GLManager::shutDown()
{
    //Deallocate program
    glDeleteProgram(programID);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //Destroy window
    SDL_DestroyWindow(window);

    //Disable text input
    SDL_StopTextInput();

    //Quit SDL subsystems
    SDL_Quit();
}