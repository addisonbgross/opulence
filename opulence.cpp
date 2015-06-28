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
#include "src/service/BufferCourier.h"
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
    BufferCourier bufferCourier;
    Model mesh, mesh1, mesh2, mesh3;
    ObjLoader loader;

    // lighting
    float sunIntensity;
    glm::vec3 pointLight = glm::vec3(-5.0, 0.0, 0.0);
    glm::vec3 sunLight;

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
        vertexShader   = loadShader("/home/champ/Git/crows/opulence/shaders/phongAttenuation.vert", gProgramID);
        fragmentShader = loadShader("/home/champ/Git/crows/opulence/shaders/phongAttenuation.frag", gProgramID);

        // TODO fix this mess
        int failCount = 0;
        while (vertexShader == 0) {
            ++failCount;
            std::cout << "Loading vertexShader failed!" << std::endl;
            vertexShader = loadShader("/home/champ/Git/crows/opulence/shaders/phongAttenuation.vert", gProgramID);

            if (failCount == 10) {
                failCount = 0;
                break;
            }
        }
        while (fragmentShader == 0) {
            ++failCount;
            std::cout << "Loading fragmentShader failed!" << std::endl;
            fragmentShader = loadShader("/home/champ/Git/crows/opulence/shaders/phongAttenuation.frag", gProgramID);
            if (failCount == 10) {
                failCount = 0;
                break;
            }
        }

        // create VAO
        glGenVertexArrays(1, &gVAO);

        glLinkProgram(gProgramID);

        //Initialize clear color
        glClearColor(0.0, 0.0, 0.0, 1.0f);

        // vertex shader variables
        bufferCourier.addAttribute("position", glGetAttribLocation(gProgramID, "position"));
        bufferCourier.addAttribute("normal", glGetAttribLocation(gProgramID, "normal"));
        bufferCourier.addUniform("model", glGetUniformLocation(gProgramID, "model"));
        bufferCourier.addUniform("view", glGetUniformLocation(gProgramID, "view"));
        bufferCourier.addUniform("proj", glGetUniformLocation(gProgramID, "proj"));
        bufferCourier.addUniform("modelPosition", glGetUniformLocation(gProgramID, "modelPosition"));
        bufferCourier.addUniform("cameraPosition", glGetUniformLocation(gProgramID, "cameraPosition"));
        bufferCourier.addUniform("pointLight", glGetUniformLocation(gProgramID, "pointLight"));

        // fragment shader variables
        bufferCourier.addAttribute("diffuse", glGetAttribLocation(gProgramID, "diffuse"));
        bufferCourier.addAttribute("specular", glGetAttribLocation(gProgramID, "specular"));
        bufferCourier.addUniform("ambientIntensity", glGetUniformLocation(gProgramID, "ambientIntensity"));
        bufferCourier.addUniform("ambientColour", glGetUniformLocation(gProgramID, "ambientColour"));
        bufferCourier.addUniform("sunIntensity", glGetUniformLocation(gProgramID, "sunIntensity"));
        bufferCourier.addUniform("sunLight", glGetUniformLocation(gProgramID, "sunLight"));

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

        /* vertex shader stuff */
        GLfloat pointIntensity = 0.1;
        glUniformMatrix4fv(bufferCourier.getUniform(("model")), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(bufferCourier.getUniform(("view")), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(bufferCourier.getUniform(("proj")), 1, GL_FALSE, &proj[0][0]);
        glUniform3fv(bufferCourier.getUniform("pointLight"), 1, &pointLight[0]);

        /* fragment shader stuff */
        GLfloat ambientIntensity = 0.05;
        glm::vec4 ambientColour = glm::vec4(1.0);
        glUniform1fv(bufferCourier.getUniform("ambientIntensity"), 1, &ambientIntensity);
        glUniform4fv(bufferCourier.getUniform("ambientColour"), 1, &ambientColour[0]);
        glUniform1fv(bufferCourier.getUniform("sunIntensity"), 1, &sunIntensity);
        glUniform3fv(bufferCourier.getUniform("sunLight"), 1, &sunLight[0]);
        glUniform3fv(bufferCourier.getUniform("cameraPosition"), 1, &camera.getEye()->x);

        bufferCourier.render();
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

        if (button == SDL_SCANCODE_UP || button == SDL_SCANCODE_DOWN ||
            button == SDL_SCANCODE_LEFT || button == SDL_SCANCODE_RIGHT) {
            glm::mat4 rotationMatrix = glm::mat4(1.0f);

            if (button == SDL_SCANCODE_UP)
                rotationMatrix = glm::rotate(rotationMatrix, 0.05f, glm::vec3(1.0f, 0.0f, 0.0f));
            else if (button == SDL_SCANCODE_DOWN)
                rotationMatrix = glm::rotate(rotationMatrix, -0.05f, glm::vec3(1.0f, 0.0f, 0.0f));

            if (button == SDL_SCANCODE_LEFT)
                rotationMatrix = glm::rotate(rotationMatrix, 0.05f, glm::vec3(0.0f, 1.0f, 0.0f));
            else if (button == SDL_SCANCODE_RIGHT)
                rotationMatrix = glm::rotate(rotationMatrix, -0.05f, glm::vec3(0.0f, 1.0f, 0.0f));

            glm::vec4 temp = rotationMatrix * glm::vec4(sunLight, 1.0f);
            sunLight.x = temp.x;
            sunLight.y = temp.y;
            sunLight.z = temp.z;
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

            glm::vec4 temp = rotationMatrix * glm::vec4(pointLight, 1.0f);
            pointLight.x = temp.x;
            pointLight.y = temp.y;
            pointLight.z = temp.z;
        }

        if (button == SDL_SCANCODE_T) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else if (button == SDL_SCANCODE_Y) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        if (button == SDL_SCANCODE_C) {
            if (bufferCourier.getNumModels() > 0) {
                bufferCourier.removeModel(0);
            }
        } else if (button == SDL_SCANCODE_V) {
            if (bufferCourier.getNumModels()  == 0) {
                bufferCourier.addModel(&mesh);
            }
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

            // enable vertex array object
            glBindVertexArray(gVAO);

            // event handler
            SDL_Event e;

            // enable text input
            SDL_StartTextInput();

            sunIntensity = 1.0;
            sunLight = glm::vec3(-1.0, -1.0, -1.0);

            obj_data house_5_obj = loader.import("res/models/obj/house_5.obj");
            obj_data house_4_obj = loader.import("res/models/obj/house_4.obj");
            mesh = Model(0, 0, 0, house_5_obj);
            mesh1 = Model(0, 0, 10, house_4_obj);

            bufferCourier.addModel(&mesh);
            //bufferCourier.addModel(&mesh1);

            /*** MAIN LOOP ***/
            bool quit = false;
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    quit = doInput(e, &camera);
                }

                // gather attributes/uniforms and render buffers
                render();

                // update screen
                SDL_GL_SwapWindow(gWindow);
            }
        }

        //Free resources and close SDL
        close();

        return 0;
    }
};