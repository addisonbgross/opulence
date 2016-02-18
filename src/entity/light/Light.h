#ifndef OPULENCE_LIGHT_H
#define OPULENCE_LIGHT_H

#include <glm/detail/type_vec4.hpp>

#include "../Entity.h"

class Light : public Entity {
private:
    GLfloat intensity;
    glm::vec4 *colour;

public:
    Light();
    Light(float x, float y, float z);
    Light(float x, float y, float z, glm::vec4 *colour);
    ~Light();

    bool isOn;

    // set
    void setIntensity(float intensity);
    void setColour(glm::vec4 *colour);

    // get
    float * getIntensity();
    glm::vec4 * getColour();
};

#endif
