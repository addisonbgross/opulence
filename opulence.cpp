#include <iostream>
#include <vector>

#include <SDL.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/entity/model/Model.h"
#include "src/entity/camera/Camera.h"
#include "src/factory/ModelFactory.h"
#include "src/factory/CameraFactory.h"
#include "src/service/GLManager.h"

class Opulence
{
private:
    //Screen dimension constants
    const GLfloat SCREEN_WIDTH = 1024.0f;
    const GLfloat SCREEN_HEIGHT = 600.0f;

    glm::vec3 zoom = glm::vec3(0.0f, 1.0f, 0.0f);

    //Camera camera;
    BufferCourier bufferCourier;
    ModelFactory *modelFactory;
    CameraFactory *cameraFactory;
    GLManager glMan;

    // lighting
    float sunIntensity;
    std::vector<glm::vec3> pointLights;
    glm::vec3 pointLight = glm::vec3(0.0, 0.0, 10.0);
    glm::vec3 sunLight;

public:
    void setZoom(float z) {
        zoom.z += z;
    }

    void setClearColour(glm::vec4 colour) {
        glClearColor(colour.r, colour.g, colour.b, colour.a);
    }

    ModelFactory * getModelFactory()
    {
        return modelFactory;
    }

    CameraFactory * getCameraFactory()
    {
        return cameraFactory;
    }

    void render() {
        /* vertex shader stuff */
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));

        glm::mat4 view = glm::lookAt(*cameraFactory->getMainCamera()->getEye(),
                                     *cameraFactory->getMainCamera()->getFocus(),
                                     *cameraFactory->getMainCamera()->getTop());

        glm::mat4 proj = glm::perspective(45.5f, SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

        /* vertex shader stuff */
        GLfloat pointIntensity = 0.1;
        glUniformMatrix4fv(bufferCourier.getUniform(("model")), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(bufferCourier.getUniform(("view")), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(bufferCourier.getUniform(("proj")), 1, GL_FALSE, &proj[0][0]);
        glUniform3fv(bufferCourier.getUniform("pointLight"), pointLights.size(), reinterpret_cast<GLfloat *>(&pointLights[0]));

        /* fragment shader stuff */
        GLfloat ambientIntensity = 0.05;
        glm::vec4 ambientColour = glm::vec4(1.0);
        glUniform1fv(bufferCourier.getUniform("ambientIntensity"), 1, &ambientIntensity);
        glUniform4fv(bufferCourier.getUniform("ambientColour"), 1, &ambientColour[0]);
        glUniform1fv(bufferCourier.getUniform("sunIntensity"), 1, &sunIntensity);
        glUniform3fv(bufferCourier.getUniform("sunLight"), 1, &sunLight[0]);
        glUniform3fv(bufferCourier.getUniform("cameraPosition"), 1, &cameraFactory->getMainCamera()->getEye()->x);

        bufferCourier.render();

        // update screen
        SDL_GL_SwapWindow(glMan.getWindow());
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

            glm::vec4 temp = rotationMatrix * glm::vec4(pointLights[0], 1.0f);
            pointLights[0].x = temp.x;
            pointLights[0].y = temp.y;
            pointLights[0].z = temp.z;
        }

        if (button == SDL_SCANCODE_T) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else if (button == SDL_SCANCODE_Y) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        return button == SDL_SCANCODE_ESCAPE || e.type == SDL_QUIT;
    }

    int start() {
        glMan.setScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);

        pointLights.push_back(glm::vec3(0, 5, 8));

        // initialize SDL
        if (!glMan.initSDL()) {
            printf("Unable to initialize SDL!\n");
        }

        // initialize OpenGL
        if (!glMan.initGL()) {
            printf("Unable to initialize OpenGL!\n");
        }

        // vertex shader variables
        GLuint gProgramID = glMan.getID();
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

        // link opengl context
        glUseProgram(glMan.getID());

        // enable vertex array object
        glBindVertexArray(glMan.getVAO());

        // enable text input
        SDL_StartTextInput();

        sunIntensity = 0.5;
        sunLight = glm::vec3(-1.0, -1.0, -1.0);

        // factories
        modelFactory = new ModelFactory();
        modelFactory->setBufferCourier(&bufferCourier);

        cameraFactory = new CameraFactory();

        return 0;
    }

    int loop() {
        // event handler
        SDL_Event e;

        /*** MAIN LOOP ***/
        bool quit = false;
        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                quit = doInput(e, cameraFactory->getMainCamera());
            }

            // gather attributes/uniforms and render buffers
            render();
        }

        //Free resources and close SDL
        glMan.shutDown();

        delete modelFactory;
        delete cameraFactory;

        return 0;
    }
};