// glm
#include <glm/glm.hpp>

// opulence
#include "src/entity/model/Model.h"
#include "src/entity/camera/Camera.h"
#include "src/entity/camera/RtsCamera.h"
#include "src/entity/light/PointLight.h"
#include "src/factory/CameraFactory.h"
#include "src/factory/LightFactory.h"
#include "src/factory/ModelFactory.h"
#include "src/service/GLManager.h"
#include "src/service/TimeManager.h"

/**
 * opulence - An OpenGL graphics renderer
 *
 * @author Addison Bellamy-Gross 2015
 */
class Opulence {
private:
    glm::mat4 model, view, proj;

    // Memory Buffers
    BufferCourier bufferCourier;

    // factory
    CameraFactory cameraFactory;
    ModelFactory modelFactory;
    LightFactory lightFactory;
    GLManager glMan;
    TimeManager timeMan;

public:
    // default screen dimension constants
    GLfloat SCREEN_WIDTH = 800.0f;
    GLfloat SCREEN_HEIGHT = 600.0f;

    Opulence() : Opulence(SCREEN_WIDTH, SCREEN_HEIGHT) {}

    Opulence(float x, float y)
    {
        glMan.setScreenSize(x, y);
        modelFactory.setBufferCourier(&bufferCourier);
        SCREEN_WIDTH = x;
        SCREEN_HEIGHT = y;
    }

    ~Opulence() {}

    void setClearColour(glm::vec4 *colour)
    {
        glClearColor(colour->r, colour->g, colour->b, colour->a);
    }

    CameraFactory * getCameraFactory()
    {
        return &cameraFactory;
    }

    LightFactory * getLightFactory()
    {
        return &lightFactory;
    }

    ModelFactory * getModelFactory()
    {
        return &modelFactory;
    }

    GLManager * getGLManager()
    {
        return &glMan;
    }

    TimeManager * getTimeManager()
    {
        return &timeMan;
    }

    void getStats()
    {
        bufferCourier.reportStats();
        //modelFactory->reportStats();
        timeMan.reportStats();
    }

    void render()
    {
        model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));

        view = glm::lookAt(*cameraFactory.getMainCamera()->getEye(),
                           *cameraFactory.getMainCamera()->getFocus(),
                           *cameraFactory.getMainCamera()->getTop());

        proj = glm::perspective(45.0f, SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 10000.0f);

        /* vertex shader stuff */
        glUniformMatrix4fv(bufferCourier.getUniform(("model")), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(bufferCourier.getUniform(("view")), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(bufferCourier.getUniform(("proj")), 1, GL_FALSE, &proj[0][0]);
        glUniform3fv(bufferCourier.getUniform("pointLight"), 1, &lightFactory.getPointLight()->position[0]);
        glUniform1fv(bufferCourier.getUniform("linearAtt"), 1, lightFactory.getPointLight()->getLinearAttenuation());
        glUniform1fv(bufferCourier.getUniform("quadraticAtt"), 1, lightFactory.getPointLight()->getQuadraticAttenuation());

        /* fragment shader stuff */
        glUniform1fv(bufferCourier.getUniform("ambientIntensity"), 1, lightFactory.getAmbientIntensity());
        glUniform4fv(bufferCourier.getUniform("ambientColour"), 1, &lightFactory.getAmbientColour()->x);
        glUniform1fv(bufferCourier.getUniform("directionalIntensity"), 1, lightFactory.getDirectionalLight()->getIntensity());
        glUniform3fv(bufferCourier.getUniform("directionalLight"), 1, &lightFactory.getDirectionalLight()->getDirection()->x);
        glUniform3fv(bufferCourier.getUniform("cameraPosition"), 1, &cameraFactory.getMainCamera()->getEye()->x);

        bufferCourier.render();

        // update screen
        SDL_GL_SwapWindow(glMan.getWindow());
    }

    glm::vec3 getClickTranslation(int x, int y)
    {
        GLfloat winX = (float)x;
        GLfloat winY = SCREEN_HEIGHT - (float)y;
        GLfloat winZ = 0;
        glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
        glm::vec3 click = glm::vec3(winX, winY, winZ);
        glm::vec4 viewPort = glm::vec4(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glm::vec3 pix = glm::unProject(click, view, proj, viewPort);

        return pix;
    }

    int start()
    {
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
        bufferCourier.addUniform("scale", glGetUniformLocation(gProgramID, "scale"));
        bufferCourier.addUniform("model", glGetUniformLocation(gProgramID, "model"));
        bufferCourier.addUniform("view", glGetUniformLocation(gProgramID, "view"));
        bufferCourier.addUniform("proj", glGetUniformLocation(gProgramID, "proj"));
        bufferCourier.addUniform("modelPosition", glGetUniformLocation(gProgramID, "modelPosition"));
        bufferCourier.addUniform("cameraPosition", glGetUniformLocation(gProgramID, "cameraPosition"));
        bufferCourier.addUniform("pointLight", glGetUniformLocation(gProgramID, "pointLight"));
        bufferCourier.addUniform("linearAtt", glGetUniformLocation(gProgramID, "linearAtt"));
        bufferCourier.addUniform("quadraticAtt", glGetUniformLocation(gProgramID, "quadraticAtt"));

        // fragment shader variables
        bufferCourier.addAttribute("diffuse", glGetAttribLocation(gProgramID, "diffuse"));
        bufferCourier.addAttribute("specular", glGetAttribLocation(gProgramID, "specular"));
        bufferCourier.addUniform("ambientIntensity", glGetUniformLocation(gProgramID, "ambientIntensity"));
        bufferCourier.addUniform("ambientColour", glGetUniformLocation(gProgramID, "ambientColour"));
        bufferCourier.addUniform("directionalIntensity", glGetUniformLocation(gProgramID, "directionalIntensity"));
        bufferCourier.addUniform("directionalLight", glGetUniformLocation(gProgramID, "directionalLight"));

        // link opengl context
        glUseProgram(glMan.getID());

        // enable vertex array object
        glBindVertexArray(glMan.getVAO());

        return 0;
    }

    void shutDown()
    {
        glMan.shutDown();
    }
};