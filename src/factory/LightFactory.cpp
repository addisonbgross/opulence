#include "LightFactory.h"

PointLight * LightFactory::makePointLight(float x, float y, float z)
{
    pointLight = new PointLight(x, y, z, new glm::vec4(1.0, 1.0, 1.0, 1.0));
    activeLights.push_back(pointLight);
    return pointLight;
}

PointLight * LightFactory::getPointLight()
{
    return this->pointLight;
}