#include <iostream>
#include <vector>

#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "src/controls/ControllerInterface.h"
#include "src/loaders/ShaderLoader.h"
#include "src/entity/Model.h"

class Opulence
{
private:
    //Screen dimension constants
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    SDL_Window *gWindow = NULL; //The window we'll be rendering to
    SDL_GLContext gContext; //OpenGL context

    //Graphics program
    GLint  gVertexPos2DLocation = -1;
    GLuint gProgramID = 0;
    GLuint gVBO[2];
    GLuint gIBO = 0;

    Keyboard keys;

public:
    bool init() {
        bool success = true;    //Initialization flag

        //Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
            success = false;

        //Use OpenGL 3.3 core
        } else {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            //Create window
            gWindow = SDL_CreateWindow("opulence v1.0",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SCREEN_WIDTH, SCREEN_HEIGHT,
                                       SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN); // full screen --> SDL_WINDOW_FULLSCREEN
            if (gWindow == NULL) {
                printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;

            } else {
                //Create context
                gContext = SDL_GL_CreateContext(gWindow);
                if (gContext == NULL) {
                    printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
                    success = false;

                } else {
                    //Initialize GLEW
                    glewExperimental = GL_TRUE;
                    GLenum glewError = glewInit();
                    if (glewError != GLEW_OK) {
                        printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
                    }

                    //Use Vsync
                    if (SDL_GL_SetSwapInterval(1) < 0) {
                        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
                    }

                    //Initialize OpenGL
                    if (!initGL()) {
                        printf("Unable to initialize OpenGL!\n");
                        success = false;
                    }
                }
            }
        }

        return success;
    }

    bool initGL() {
        //Success flag
        bool success = true;

        //Generate program
        gProgramID = glCreateProgram();

        //Create vertex shader
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // vertex array object
        GLuint vaoId = 0;
        glGenVertexArrays(1, &vaoId);
        glBindVertexArray(vaoId);

        loadShader("/home/champ/Git/crows/opulence/shaders/shader1.vert", gProgramID);
        loadShader("/home/champ/Git/crows/opulence/shaders/shader1.frag", gProgramID);

        glLinkProgram(gProgramID);

        gVertexPos2DLocation = glGetAttribLocation(gProgramID, "centreVertex");
        if (gVertexPos2DLocation == -1) {
            printf("centreVertex is not a valid glsl program variable!\n");
            success = false;

        } else {
            //Initialize clear color
            glClearColor(0.f, 0.f, 0.f, 1.f);

            //Create VBO
            glGenBuffers(2, &gVBO[0]);

            //Create IBO
            glGenBuffers(1, &gIBO);
        }

        return success;
    }

    void update() {
        //No per frame update needed
    }

    void render() {
        //Clear color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // bind program
        glUseProgram(gProgramID);

        //VBO data
        std::vector<GLfloat> vertexData = {
                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, 0.5f, -0.5f,
                -0.5f, 0.5f, -0.5f,

                -0.5f, -0.5f, 0.5f,
                0.5f, -0.5f, 0.5f,
                0.5f, 0.5f, 0.5f,
                -0.5f, 0.5f, 0.5f
        };

        //IBO data
        std::vector<GLuint> indexData = {0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7};

        Model *square = new Model(0, 0, 0, vertexData, indexData);

        glm::vec4 c = keys.update();
        GLfloat colourData[] = { c.r, c.g, c.b, c.a };

        // set index data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, square->getNumIndexVerts() * sizeof(GLuint), square->getIndexVerts(), GL_STATIC_DRAW);

        //Set vertex data
        glBindBuffer(GL_ARRAY_BUFFER, gVBO[0]);
        glBufferData(GL_ARRAY_BUFFER, square->getNumPositionVerts() * sizeof(GLfloat), square->getPositionVerts(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(gVertexPos2DLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);

        //Set index data and render
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        //Disable vertex position
        glDisableVertexAttribArray(gVertexPos2DLocation);
    }

    void close() {
        //Deallocate program
        glDeleteProgram(gProgramID);

        //Destroy window
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;

        //Quit SDL subsystems
        SDL_Quit();
    }

    int start() {
        //Start up SDL and create window
        if (!init()) {
            printf("Failed to initialize!\n");

        } else {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Enable text input
            SDL_StartTextInput();

            //While application is running
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                //Render quad
                render();

                //Update screen
                SDL_GL_SwapWindow(gWindow);
            }

            //Disable text input
            SDL_StopTextInput();
        }

        //Free resources and close SDL
        close();

        return 0;
    }
};