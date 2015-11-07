#ifndef OPULENCE_ENTITY_H
#define OPULENCE_ENTITY_H

// general
#include <iostream>

// opulence
#include <GL/glew.h>
#include <GL/gl.h>

// glm
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity {
public:
    int id;
    std::string name;
    glm::vec3 position;
    glm::quat orientation;
    glm::mat4 orientationReference;

    Entity();
    Entity(float x, float y, float z);
    ~Entity();

    // get
    virtual float getWidth();
    virtual float getHeight();
    virtual float getDepth();
    glm::quat * getOrientationQuat();
    GLfloat * getOrientation();

    // set
    void setOrientation(glm::quat q);
};

#endif
