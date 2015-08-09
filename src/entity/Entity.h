#ifndef OPULENCE_ENTITY_H
#define OPULENCE_ENTITY_H

#include <glm/detail/type_vec3.hpp>

class Entity {
public:
    float x, y, z;
    float scale = 1.0f;
    glm::vec3 position;

    Entity();
    ~Entity();

    // get
    glm::vec3 * getPosition();
};

#endif
