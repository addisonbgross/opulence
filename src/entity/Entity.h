#ifndef OPULENCE_ENTITY_H
#define OPULENCE_ENTITY_H

#include "model/Model.h"

class Entity {
private:
    std::vector<Model> models;
    glm::vec3 position;

public:
    Entity(glm::vec3 position);
    Entity(glm::vec3 position, Model models...);
    Model getModel();
    std::vector<Model> getAllModels();

};

#endif //OPULENCE_ENTITY_H
