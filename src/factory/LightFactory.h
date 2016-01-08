#ifndef OPULENCE_LIGHTFACTORY_H
#define OPULENCE_LIGHTFACTORY_H

#include <vector>
#include <iostream>

#include "../entity/light/Light.h"
#include "../entity/light/DirectionalLight.h"
#include "../entity/light/PointLight.h"

class LightFactory {
private:
    std::vector<PointLight *> pointLights;
    std::vector<float> pointLightPositions;
    std::vector<float> pointLightLinearAttenuations;
    std::vector<float> pointLightQuadraticAttenuations;

    glm::vec4 *ambientColour;
    float ambientIntensity;

    glm::vec4 *directionalColour;
    DirectionalLight *directionalLight;
    float directionalIntensity;

public:
    LightFactory();
    ~LightFactory();

    DirectionalLight * makeDirectionalLight(glm::vec4 *colour);
    DirectionalLight * makeDirectionalLight(glm::vec4 *colour, glm::vec3 *direction);
    PointLight * makePointLight(float x, float y, float z);

    // set
    void setAmbientColour(glm::vec4 *colour);
    void setAmbientIntensity(float i);
    void setDirectionalColour(glm::vec4 *colour);
    void setDirectionalIntensity(float i);

    // get
    glm::vec4 * getAmbientColour();
    float * getAmbientIntensity();
    DirectionalLight * getDirectionalLight();
    float * getDirectionalIntensity();

    // PointLights
    PointLight * getPointLights();
    float * getPointLightPositions();
    float * getPointLightLinearAttenuations();
    float * getPointLightQuadradticAttenuations();
};

#endif
