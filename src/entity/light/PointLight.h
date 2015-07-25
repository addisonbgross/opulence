#ifndef OPULENCE_POINTLIGHT_H
#define OPULENCE_POINTLIGHT_H

#include "Light.h"

class PointLight : public Light {
private:

public:
    PointLight(float x, float y, float z);
    PointLight(float x, float y, float z, glm::vec4 *colour);
    ~PointLight();
};

#endif
