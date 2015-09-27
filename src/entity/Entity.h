#ifndef OPULENCE_ENTITY_H
#define OPULENCE_ENTITY_H

#include <iostream>
#include <glm/detail/type_vec3.hpp>

class Entity {
public:
    int id;
    std::string name;
    glm::vec3 position;

    Entity();
    Entity(float x, float y, float z);
    ~Entity();

    virtual float getWidth();
    virtual float getHeight();
    virtual float getDepth();
};

#endif
