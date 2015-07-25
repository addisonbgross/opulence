#ifndef OPULENCE_LIGHT_H
#define OPULENCE_LIGHT_H

#include <GL/gl.h>
#include <glm/detail/type_vec4.hpp>

#include "../Entity.h"

class Light : public Entity {
private:
    glm::vec4 *colour;

public:
    Light(GLfloat x, GLfloat y, GLfloat z);
    Light(GLfloat x, GLfloat y, GLfloat z, glm::vec4 *colour);
    ~Light();

    // set
    void setColour(glm::vec4 *colour);

    // get
    glm::vec4 * getColour();
};

#endif
