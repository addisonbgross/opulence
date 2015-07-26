#ifndef OPULENCE_DIRECTIONALLIGHT_H
#define OPULENCE_DIRECTIONALLIGHT_H

#include "Light.h"

class DirectionalLight : public Light {
private:
    glm::vec3 *direction;

public:
    DirectionalLight();
    ~DirectionalLight();
    DirectionalLight(glm::vec4 *colour);
    DirectionalLight(glm::vec4 *colour, glm::vec3 *direction);

    // set
    void setDirection(glm::vec3 *direction);

    // get
    glm::vec3 * getDirection();
};

#endif
