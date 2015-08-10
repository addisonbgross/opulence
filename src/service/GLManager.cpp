#include "GLManager.h"

/**
 * initGL() - create and configure OpenGL resources
 *
 * @return bool true if initialization is a success
 */
bool GLManager::initGL()
{
    // success flag
    bool success = true;

    // generate program
    programID = glCreateProgram();

    // enable z-buffer face culling
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // transparency
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // enable vsync rate
    if (SDL_GL_SetSwapInterval(1) < 0)
        std::cout << "Swap Interval could not be set!" << std::endl;

    // vertex & fragment shaders
    vertexShader   = 0;
    fragmentShader = 0;
    ShaderLoader loader;

    // load vertex shader
    int failCount = 0;
    while (vertexShader == 0) {
        vertexShader = loader.loadShader("/home/champ/Git/crows/opulence/shaders/phongAttenuation.vert", programID);
        ++failCount;
        if (failCount == 10) {
            std::cout << "Loading vertexShader failed!" << std::endl;
            failCount = 0;
            break;
        }
    }

    // load fragment shader
    while (fragmentShader == 0) {
        fragmentShader = loader.loadShader("/home/champ/Git/crows/opulence/shaders/phongAttenuation.frag", programID);
        ++failCount;
        if (failCount == 10) {
            std::cout << "Loading fragmentShader failed!" << std::endl;
            break;
        }
    }

    // create VAO
    glGenVertexArrays(1, &VAO);

    // link OpenGL program
    glLinkProgram(programID);

    //Initialize clear color
    glClearColor(0.0, 0.0, 0.0, 1.0f);

    return success;
}

/**
 * initSDL() - create and configure native windowing system
 *
 * @return bool true if initialization is a success
 */
bool GLManager::initSDL()
{
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;

    //Use OpenGL 3.3 core
    } else {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

        // allow for multisampling of frame buffer
        glEnable(GL_MULTISAMPLE);

        //Create window
        window = SDL_CreateWindow("opulence v1.0",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   this->screenWidth, this->screenHeight,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

        surface = SDL_GetWindowSurface(window);

        SDL_GL_CreateContext(window);

        // initialize GLEW system independence
        glewExperimental = GL_TRUE;
        GLenum glewError = glewInit();

        //Use Vsync
        if (SDL_GL_SetSwapInterval(1) < 0) {
            printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
        }

    }

    return success;
}

/**
 * shutDown() - free resources maintaining OpenGL context
 *              and free event handlers
 */
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

/**
 * getID() - get OpenGL context's id
 *
 * @return GLuint current OpenGL context
 */
GLuint GLManager::getID()
{
    return programID;
}

/**
 * getVertexShader() - get current vertex shader's handle in the OpenGL context
 *
 * @return GLuint current vertex shader in use
 */
GLuint GLManager::getVertexShader()
{
    return vertexShader;
}

/**
 * getFragmentShader() - get current fragment shader's handle in the OpenGL context
 *
 * @return GLuint current fragment shader in use
 */
GLuint GLManager::getFragmentShader()
{
    return fragmentShader;
}

/**
 * getVAO() - get current vertex array object's handle in the OpenGL context
 *
 * @return GLuint current vertex array object in use
 */
GLuint GLManager::getVAO()
{
    return VAO;
}

/**
 * getWindow() - get current SDL window containing the current
 *               frame buffer and native windowing system settings
 *
 * @return SDL_Window* current SDL window in use
 */
SDL_Window * GLManager::getWindow()
{
    return window;
}

/**
 * getSurface() - get current SDL window's frame buffer
 *
 * @return SDL_Surface* current SDL window's frame buffer
 */
SDL_Surface * GLManager::getSurface()
{
    return surface;
}

/**
 * setScreenSize() - set resolution of opulence window
 *
 * @params w,h width and height in pixels
 */
void GLManager::setScreenSize(GLfloat w, GLfloat h)
{
    screenWidth = w;
    screenHeight = h;
}
