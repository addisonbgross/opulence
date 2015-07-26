#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
    this->direction = new glm::vec3();
}

DirectionalLight::~DirectionalLight()
{
    delete this->direction;
}

DirectionalLight::DirectionalLight(glm::vec4 *colour) : Light(0, 0, 0, colour)
{
    this->direction = new glm::vec3(0.0, 0.0, -1.0);
}

DirectionalLight::DirectionalLight(glm::vec4 *colour, glm::vec3 *direction) : DirectionalLight(colour)
{
    this->direction = direction;
}

/*** set ***/

void DirectionalLight::setDirection(glm::vec3 *direction)
{
    this->direction = direction;
}

/*** get ***/

glm::vec3 * DirectionalLight::getDirection()
{
    return this->direction;
}