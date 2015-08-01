#include "LightFactory.h"

LightFactory::LightFactory()
{
    ambientColour = new glm::vec4(1.0, 1.0, 1.0, 1.0);
    ambientIntensity = 0.2;
}

LightFactory::~LightFactory()
{
    delete ambientColour;
}

DirectionalLight * LightFactory::makeDirectionalLight(glm::vec4 *colour)
{
    directionalLight = new DirectionalLight(colour);
    activeLights.push_back(directionalLight);
    return directionalLight;
}

DirectionalLight * LightFactory::makeDirectionalLight(glm::vec4 *colour, glm::vec3 *direction)
{
    directionalLight = new DirectionalLight(colour, direction);
    activeLights.push_back(directionalLight);
    return directionalLight;
}

PointLight * LightFactory::makePointLight(float x, float y, float z)
{
    pointLight = new PointLight(x, y, z, new glm::vec4(1.0, 1.0, 1.0, 1.0));
    activeLights.push_back(pointLight);
    return pointLight;
}

/*** setters ***/

void LightFactory::setAmbientColour(glm::vec4 *colour)
{
    ambientColour = colour;
}

void LightFactory::setAmbientIntensity(float i)
{
    ambientIntensity = i;
}

/*** getters ***/

glm::vec4 * LightFactory::getAmbientColour()
{
    return ambientColour;
}

float * LightFactory::getAmbientIntensity()
{
    return &ambientIntensity;
}

DirectionalLight * LightFactory::getDirectionalLight()
{
    return this->directionalLight;
}

PointLight * LightFactory::getPointLight()
{
    return this->pointLight;
}