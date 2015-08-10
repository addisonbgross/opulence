#ifndef OPULENCE_ENTITY_H
#define OPULENCE_ENTITY_H

#include <glm/detail/type_vec3.hpp>

class Entity {
public:
    glm::vec3 position;

    Entity();
    Entity(float x, float y, float z);
    ~Entity();
};

#endif
