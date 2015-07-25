#include <iostream>
#include <vector>

#include <SDL.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/entity/model/Model.h"
#include "src/entity/camera/Camera.h"
#include "src/entity/light/PointLight.h"

#include "src/factory/CameraFactory.h"
#include "src/factory/LightFactory.h"
#include "src/factory/ModelFactory.h"

#include "src/service/GLManager.h"

/**
 * opulence: An OpenGL graphics renderer.
 * Written by Addison Bellamy-Gross 2015
 */
class Opulence {
private:
    //Screen dimension constants
    const GLfloat SCREEN_WIDTH = 1024.0f;
    const GLfloat SCREEN_HEIGHT = 600.0f;

    glm::vec3 zoom = glm::vec3(0.0f, 1.0f, 0.0f);

    // camera;
    BufferCourier bufferCourier;

    // factory
    CameraFactory *cameraFactory;
    ModelFactory *modelFactory;
    LightFactory *lightFactory;
    GLManager glMan;

    // lighting
    float sunIntensity;
    PointLight *pointLight = new PointLight(20.0, 5.0, 5.0);
    glm::vec3 sunLight;

public:
    void setZoom(float z)
    {
        zoom.z += z;
    }

    void setClearColour(glm::vec4 colour)
    {
        glClearColor(colour.r, colour.g, colour.b, colour.a);
    }

    CameraFactory * getCameraFactory()
    {
        return cameraFactory;
    }

    LightFactory * getLightFactory()
    {
        return lightFactory;
    }

    ModelFactory * getModelFactory()
    {
        return modelFactory;
    }

    void render()
    {
        /* vertex shader stuff */
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));

        glm::mat4 view = glm::lookAt(*cameraFactory->getMainCamera()->getEye(),
                                     *cameraFactory->getMainCamera()->getFocus(),
                                     *cameraFactory->getMainCamera()->getTop());

        glm::mat4 proj = glm::perspective(45.5f, SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);

        /* vertex shader stuff */
        GLfloat pointIntensity = 0.05;
        glUniformMatrix4fv(bufferCourier.getUniform(("model")), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(bufferCourier.getUniform(("view")), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(bufferCourier.getUniform(("proj")), 1, GL_FALSE, &proj[0][0]);
        glUniform3fv(bufferCourier.getUniform("pointLight"), 1, &lightFactory->getPointLight()->position[0]);

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

    int start()
    {
        glMan.setScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);

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

        sunIntensity = 0.1;
        sunLight = glm::vec3(-1.0, -1.0, -1.0);
        pointLight->setColour(new glm::vec4(1.0, 1.0, 1.0, 1.0));

        // factory constructors
        cameraFactory = new CameraFactory();
        lightFactory = new LightFactory();
        modelFactory = new ModelFactory();
        modelFactory->setBufferCourier(&bufferCourier);

        return 0;
    }
};