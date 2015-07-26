#ifndef OPULENCE_LIGHTFACTORY_H
#define OPULENCE_LIGHTFACTORY_H

#include <vector>
#include <iostream>

#include "../entity/light/Light.h"
#include "../entity/light/DirectionalLight.h"
#include "../entity/light/PointLight.h"

class LightFactory {
private:
    std::vector<Light *> activeLights;
    DirectionalLight *directionalLight;
    PointLight *pointLight;

public:
    DirectionalLight * makeDirectionalLight(glm::vec4 *colour);
    DirectionalLight * makeDirectionalLight(glm::vec4 *colour, glm::vec3 *direction);
    PointLight * makePointLight(float x, float y, float z);

    // get
    DirectionalLight * getDirectionalLight();
    PointLight * getPointLight();
};

#endif
