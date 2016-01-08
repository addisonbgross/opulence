#include "Light.h"

Light::Light()
{
    this->intensity = 0.3;
    this->position.x = 0.0f;
    this->position.y = 0.0f;
    this->position.z = 0.0f;
    this->colour = new glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
};

Light::Light(float x, float y, float z)
{
    this->intensity = 0.3;
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
    this->colour = new glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

Light::Light(float x, float y, float z, glm::vec4 *colour)
{
    this->intensity = 0.3;
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

void Light::setIntensity(float intensity)
{
    this->intensity = intensity;
}

void Light::setColour(glm::vec4 *colour)
{
    this->colour->x = colour->x;
    this->colour->y = colour->y;
    this->colour->z = colour->z;
    this->colour->w = colour->w;
}

/*** get ***/

float * Light::getIntensity()
{
    return &this->intensity;
}

glm::vec4 * Light::getColour()
{
    return this->colour;
}
