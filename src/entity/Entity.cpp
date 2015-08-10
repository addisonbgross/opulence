#include <glm/detail/type_vec3.hpp>
#include "Entity.h"

Entity::Entity()
{
    this->position = glm::vec3(0, 0, 0);
}

Entity::Entity(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

Entity::~Entity() {}
