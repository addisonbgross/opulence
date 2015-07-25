#ifndef OPULENCE_LIGHTFACTORY_H
#define OPULENCE_LIGHTFACTORY_H

#include <vector>
#include <iostream>

#include "../entity/light/Light.h"
#include "../entity/light/PointLight.h"

class LightFactory {
private:
    std::vector<Light *> activeLights;
    PointLight *pointLight;

public:
    PointLight * makePointLight(float x, float y, float z);

    // get
    PointLight * getPointLight();
};

#endif
