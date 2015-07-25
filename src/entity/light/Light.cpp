#include "Light.h"

Light::Light(float x, float y, float z)
{
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
}

Light::Light(float x, float y, float z, glm::vec4 *colour)
{
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
    this->colour = colour;
}

Light::~Light()
{
    delete this->colour;
}

/*** set ***/
void Light::setColour(glm::vec4 *colour)
{
    this->colour = colour;
}

/*** get ***/
glm::vec4 *Light::getColour()
{
    return this->colour;
}
