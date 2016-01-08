#include "PointLight.h"

PointLight::PointLight(float x, float y, float z) : Light(x, y, z)
{
    this->linearAttenuation = 0.045;
    this->quadraticAttenuation = 0.0075;
}

PointLight::PointLight(float x, float y, float z, glm::vec4 *colour) : Light(x, y, z, colour)
{
    this->linearAttenuation = 0.045;
    this->quadraticAttenuation = 0.0075;
}

PointLight::~PointLight() {}

/*** set ***/

void PointLight::setLinearAttenuation(float linear)
{
    this->linearAttenuation = linear;
}

void PointLight::setQuadraticAttenuation(float quadratic)
{
    this->quadraticAttenuation = quadratic;
}

/*** get ***/

float * PointLight::getLinearAttenuation()
{
    return &this->linearAttenuation;
}

float * PointLight::getQuadraticAttenuation()
{
    return &this->quadraticAttenuation;
}
