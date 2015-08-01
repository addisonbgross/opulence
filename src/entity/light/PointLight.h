#ifndef OPULENCE_POINTLIGHT_H
#define OPULENCE_POINTLIGHT_H

#include "Light.h"

class PointLight : public Light {
private:
    GLfloat linearAttenuation;
    GLfloat quadraticAttenuation;

public:
    PointLight();
    PointLight(float x, float y, float z);
    PointLight(float x, float y, float z, glm::vec4 *colour);
    ~PointLight();

    // set
    void setLinearAttenuation(float linear);
    void setQuadraticAttenuation(float quadratic);

    // get
    GLfloat * getLinearAttenuation();
    GLfloat * getQuadraticAttenuation();
};

#endif