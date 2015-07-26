#include "Light.h"

Light::Light()
{
    this->intensity = 0.3;
    this->colour = new glm::vec4();
};

Light::Light(float x, float y, float z) : Light()
{
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
}

Light::Light(float x, float y, float z, glm::vec4 *colour) : Light()
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

void Light::setIntensity(GLfloat intensity)
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

GLfloat * Light::getIntensity()
{
    return &this->intensity;
}

glm::vec4 *Light::getColour()
{
    return this->colour;
}
