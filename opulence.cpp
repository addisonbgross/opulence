#include <iostream>
#include <vector>

#include <SDL.h>
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/loaders/ShaderLoader.h"
#include "src/entity/model/Model.h"
#include "src/entity/camera/Camera.h"

// TODO extract
#include "controls/ControllerInterface.h"
#include "controls/Mouse.h"

class Opulence
{
private:
    //Screen dimension constants
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    SDL_Window *gWindow = NULL; //The window we'll be rendering to
    SDL_GLContext gContext; //OpenGL context

    //Graphics program
    GLuint vertexShader, fragmentShader;
    // vertex shader
    GLint  gPosition, gModel, gView, gProj;
    // fragment shader
    GLint  gColour, gAmbient;
    GLuint gProgramID = 0;
    std::vector<GLuint> *gVBO;
    std::vector<GLuint> *gVAO;
    std::vector<GLuint> *gIBO;

    glm::vec3 zoom = glm::vec3(0.0f, 1.0f, 0.0f);

    Keyboard keys;
    Mouse mouse;
    Camera *camera;

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
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

            //Create window
            gWindow = SDL_CreateWindow("opulence v1.0",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SCREEN_WIDTH, SCREEN_HEIGHT,
                                       SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN); // full screen --> SDL_WINDOW_FULLSCREEN

            SDL_GLContext glcontext(SDL_GL_CreateContext(gWindow));

            glewExperimental = GL_TRUE;
            GLenum glewError = glewInit();

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

        return success;
    }

    bool initGL() {
        // success flag
        bool success = true;

        // generate program
        gProgramID = glCreateProgram();

        // vertex & fragment
        vertexShader   = loadShader("/home/champ/Git/crows/opulence/shaders/shader1.vert", gProgramID);
        fragmentShader = loadShader("/home/champ/Git/crows/opulence/shaders/shader1.frag", gProgramID);

        // create openGL buffer objects
        GLuint buffer;
        // create VAO
        gVAO = new std::vector<GLuint>();
        glGenVertexArrays(1, &buffer);
        gVAO->push_back(buffer);

        // create VBO
        gVBO = new std::vector<GLuint>();
        glGenBuffers(1, &buffer);
        gVBO->push_back(buffer);
        glGenBuffers(1, &buffer);
        gVBO->push_back(buffer);

        // create IBO
        gIBO = new std::vector<GLuint>();
        glGenBuffers(1, &buffer);
        gIBO->push_back(buffer);

        glLinkProgram(gProgramID);

        //Initialize clear color
        glClearColor(0.f, 0.f, 0.f, 1.f);

        // vertex shader variables
        gPosition = glGetAttribLocation(gProgramID, "position");
        gModel    = glGetUniformLocation(gProgramID, "model");
        gView     = glGetUniformLocation(gProgramID, "view");
        gProj     = glGetUniformLocation(gProgramID, "proj");

        // fragment shader variables
        gColour   = glGetAttribLocation(gProgramID, "colour");
        gAmbient  = glGetUniformLocation(gProgramID, "ambient");
        if (gAmbient < 0)
            std::cout << "gAmbient failed!" << std::endl;
        if (gColour < 0)
            std::cout << "gColour failed!" << std::endl;

        return success;
    }

    void setZoom(float z) {
        zoom.z += z;
    }

    void setClearColour(glm::vec4 colour) {
        glClearColor(colour.r, colour.g, colour.b, colour.a);
    }

    void update() {
        //No per frame update needed
    }

    void render() {
        //Clear color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        //VBO data
        std::vector<GLfloat> vertexData = {
                -0.5f, -0.5f, 0.5f,
                0.5f, -0.5f, 0.5f,
                0.5f, 0.5f, 0.5f,
                -0.5f, 0.5f, 0.5f,

                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, 0.5f, -0.5f,
                -0.5f, 0.5f, -0.5f
        };

        std::vector<GLfloat> vertexColours = {
                1.0, 0.0, 0.0, 1.0,
                0.0, 1.0, 0.0, 1.0,
                0.0, 0.0, 1.0, 1.0,
                0.0, 0.0, 0.0, 1.0,

                1.0, 0.0, 0.0, 1.0,
                0.0, 1.0, 0.0, 1.0,
                0.0, 0.0, 1.0, 1.0,
                1.0, 1.0, 1.0, 1.0
        };

        //IBO data
        std::vector<GLuint> indexData = {
                // front
                0, 1, 2,
                2, 3, 0,
                // top
                3, 2, 6,
                6, 7, 3,
                // back
                7, 6, 5,
                5, 4, 7,
                // bottom
                4, 5, 1,
                1, 0, 4,
                // left
                4, 0, 3,
                3, 7, 4,
                // right
                1, 5, 6,
                6, 2, 1
        };


        /* vertex shader stuff */
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));

        glm::mat4 view = glm::lookAt(*camera->getEye(),
                                     *camera->getFocus(),
                                     *camera->getTop());

        glm::mat4 proj = glm::perspective(45.0f, 800.0f/600.0f, 0.1f, 10.0f);

        glUniformMatrix4fv(gModel, 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(gView, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(gProj, 1, GL_FALSE, &proj[0][0]);

        /* fragment shader stuff */
        glm::vec4 light = glm::vec4(0.5);
        glUniform4fv(gAmbient, 1, &light[0]);

        Model *square = new Model(0, 0, 0, vertexData, indexData, vertexColours);

        glUseProgram(gProgramID);

        glBindVertexArray(gVAO->at(0));

        // set index data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO->at(0));
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     square->getNumIndexVerts() * sizeof(GLuint),
                     square->getIndexVerts(),
                     GL_STATIC_DRAW);

        // set vertex data
        glBindBuffer(GL_ARRAY_BUFFER, gVBO->at(0));
        glBufferData(GL_ARRAY_BUFFER,
                     square->getNumPositionVerts() * sizeof(GLfloat),
                     square->getPositionVerts(),
                     GL_STATIC_DRAW);
        glVertexAttribPointer(gPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // set colour data
        glBindBuffer(GL_ARRAY_BUFFER, gVBO->at(1));
        glBufferData(GL_ARRAY_BUFFER,
                     square->getNumColourVerts() * sizeof(GLfloat),
                     square->getColourVerts(),
                     GL_STATIC_DRAW);
        glVertexAttribPointer(gColour, 4, GL_FLOAT, GL_FALSE, 0, 0);

        // enable variables within shader pipeline
        glEnableVertexAttribArray(gPosition);
        glEnableVertexAttribArray(gColour);

        // set index data and render
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO->at(0));
        //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, NULL);

        // free shader variables
        glDisableVertexAttribArray(gPosition);
        glDisableVertexAttribArray(gColour);
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

            // create camera 1
            camera = new Camera();

            //While application is running
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION) {
                        // camera movement
                        camera->setEye(mouse.getButtons( e, camera->getEye() ) );
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