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
    Light(GLfloat x, GLfloat y, GLfloat z);
    Light(GLfloat x, GLfloat y, GLfloat z, glm::vec4 *colour);
    ~Light();

    // set
    void setIntensity(GLfloat intensity);
    void setColour(glm::vec4 *colour);

    // get
    GLfloat * getIntensity();
    glm::vec4 * getColour();
};

#endif
