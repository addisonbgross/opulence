#include <iostream>
#include <vector>

#include <SDL.h>
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/entity/model/Model.h"
#include "src/entity/camera/Camera.h"
#include "src/service/Courier.h"
#include "src/loaders/ShaderLoader.h"

class Opulence
{
private:
    //Screen dimension constants
    const GLfloat SCREEN_WIDTH = 1024.0;
    const GLfloat SCREEN_HEIGHT = 600.0;

    SDL_Window *gWindow = NULL; //The window we'll be rendering to
    SDL_GLContext gContext; //OpenGL context

    //Graphics program
    GLuint vertexShader = 0, fragmentShader = 0;
    GLuint gProgramID = 0;
    GLuint gVAO = 0;

    glm::vec3 zoom = glm::vec3(0.0f, 1.0f, 0.0f);

    Camera camera;
    Courier courier;
    Model mesh, *mesh1, *mesh2, *mesh3;
    glm::vec3 light;

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

        // enable z-buffer face culling
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glShadeModel(GL_FLAT);

        // enable vsync rate
        if (SDL_GL_SetSwapInterval(1) < 0)
            std::cout << "Swap Interval could not be set!" << std::endl;

        // vertex & fragment
        vertexShader   = loadShader("/home/champ/Git/crows/opulence/shaders/blinnPhong.vert", gProgramID);
        fragmentShader = loadShader("/home/champ/Git/crows/opulence/shaders/blinnPhong.frag", gProgramID);

        while (vertexShader == 0) {
            std::cout << "Loading vertexShader failed!" << std::endl;
            vertexShader = loadShader("/home/champ/Git/crows/opulence/shaders/blinnPhong.vert", gProgramID);
        }
        while (fragmentShader == 0) {
            std::cout << "Loading fragmentShader failed!" << std::endl;
            fragmentShader = loadShader("/home/champ/Git/crows/opulence/shaders/blinnPhong.frag", gProgramID);
        }

        // create VAO
        glGenVertexArrays(1, &gVAO);

        glLinkProgram(gProgramID);

        //Initialize clear color
        glClearColor(0.0, 0.0, 0.0, 1.0f);

        // vertex shader variables
        courier.addAttribute("position", glGetAttribLocation(gProgramID, "position"));
        courier.addAttribute("normal", glGetAttribLocation(gProgramID, "normal"));
        courier.addUniform("model", glGetUniformLocation(gProgramID, "model"));
        courier.addUniform("view", glGetUniformLocation(gProgramID, "view"));
        courier.addUniform("proj", glGetUniformLocation(gProgramID, "proj"));
        courier.addUniform("modelPosition", glGetUniformLocation(gProgramID, "modelPosition"));
        courier.addUniform("cameraPosition", glGetUniformLocation(gProgramID, "cameraPosition"));

        // fragment shader variables
        courier.addAttribute("diffuse", glGetAttribLocation(gProgramID, "diffuse"));
        courier.addAttribute("specular", glGetAttribLocation(gProgramID, "specular"));
        courier.addUniform("directionalLight", glGetUniformLocation(gProgramID, "directionalLight"));
        courier.addUniform("ambientIntensity", glGetUniformLocation(gProgramID, "ambientIntensity"));
        courier.addUniform("ambientColour", glGetUniformLocation(gProgramID, "ambientColour"));

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* vertex shader stuff */
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));

        glm::mat4 view = glm::lookAt(*camera.getEye(),
                                     *camera.getFocus(),
                                     *camera.getTop());

        glm::mat4 proj = glm::perspective(45.5f, SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

        glUniformMatrix4fv(courier.getUniform(("model")), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(courier.getUniform(("view")), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(courier.getUniform(("proj")), 1, GL_FALSE, &proj[0][0]);

        /* fragment shader stuff */
        GLfloat ambientIntensity = 0.1;
        glm::vec4 ambientColour = glm::vec4(1.0);
        glUniform1fv(courier.getUniform("ambientIntensity"), 1, &ambientIntensity);
        glUniform4fv(courier.getUniform("ambientColour"), 1, &ambientColour[0]);
        glUniform3fv(courier.getUniform("directionalLight"), 1, &light[0]);
        glUniform3fv(courier.getUniform("cameraPosition"), 1, &camera.getEye()->x);

        glBindVertexArray(gVAO);

        courier.sendBuffers();
    }

    void close() {
        //Deallocate program
        glDeleteProgram(gProgramID);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        //Destroy window
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;

        //Disable text input
        SDL_StopTextInput();

        //Quit SDL subsystems
        SDL_Quit();
    }

    bool doInput(SDL_Event e, Camera *camera) {
        GLuint button = e.button.button;
        if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEWHEEL) {
            if (button == SDL_BUTTON_LEFT) {
                if (e.motion.yrel > 0) {
                    camera->rotateVertical(-0.025f);
                } else if (e.motion.yrel < 0) {
                    camera->rotateVertical(0.025f);
                }

                if (e.motion.xrel > 0) {
                    camera->rotateHorizontal(-0.025f);
                } else if (e.motion.xrel < 0) {
                    camera->rotateHorizontal(0.025f);
                }
            }
        }

        if (e.type == SDL_MOUSEWHEEL) {
            if (e.wheel.y < 0) {
                camera->incrementZoom();
            } else if (e.wheel.y > 0) {
                camera->decrementZoom();
            }
        }

        if (button == SDL_SCANCODE_W || button == SDL_SCANCODE_S ||
                button == SDL_SCANCODE_A || button == SDL_SCANCODE_D) {
            glm::mat4 rotationMatrix = glm::mat4(1.0f);

            if (button == SDL_SCANCODE_W)
                rotationMatrix = glm::rotate(rotationMatrix, 0.05f, glm::vec3(1.0f, 0.0f, 0.0f));
            else if (button == SDL_SCANCODE_S)
                rotationMatrix = glm::rotate(rotationMatrix, -0.05f, glm::vec3(1.0f, 0.0f, 0.0f));

            if (button == SDL_SCANCODE_A)
                rotationMatrix = glm::rotate(rotationMatrix, 0.05f, glm::vec3(0.0f, 1.0f, 0.0f));
            else if (button == SDL_SCANCODE_D)
                rotationMatrix = glm::rotate(rotationMatrix, -0.05f, glm::vec3(0.0f, 1.0f, 0.0f));

            glm::vec4 temp = rotationMatrix * glm::vec4(light, 1.0f);
            light.x = temp.x;
            light.y = temp.y;
            light.z = temp.z;
        }

        if (button == SDL_SCANCODE_T) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else if (button == SDL_SCANCODE_Y) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        if (button == SDL_SCANCODE_PERIOD) {
            camera->incrementZoom();
        } else if (button == SDL_SCANCODE_COMMA) {
            camera->decrementZoom();
        }

        if (button == SDL_SCANCODE_LEFT) {
            camera->moveLeft();
        } else if (button == SDL_SCANCODE_RIGHT) {
            camera->moveRight();
        }

        if (button == SDL_SCANCODE_UP) {
            camera->moveUp();
        } else if (button == SDL_SCANCODE_DOWN) {
            camera->moveDown();
        }

        return button == SDL_SCANCODE_ESCAPE || e.type == SDL_QUIT;
    }

    int start() {
        //Start up SDL and create window
        if (!init()) {
            printf("Failed to initialize!\n");

        } else {
            // link opengl context
            glUseProgram(gProgramID);

            // event handler
            SDL_Event e;

            // enable text input
            SDL_StartTextInput();

            ObjLoader loader;
            obj_data objModel = loader.import("res/models/obj/hiMonkey.obj");
            mesh = Model(0, 0, 0, objModel);

            courier.addModel(&mesh);

            light = glm::vec3(0.0, 1.0, -1.0);

            /*** MAIN LOOP ***/
            bool quit = false;
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    quit = doInput(e, &camera);
                }

                //Render quad
                render();

                //Update screen
                SDL_GL_SwapWindow(gWindow);
            }
        }

        //Free resources and close SDL
        close();

        return 0;
    }
};