#include "PointLight.h"

PointLight::PointLight(float x, float y, float z) : Light(x, y, z) {}

PointLight::PointLight(float x, float y, float z, glm::vec4 *colour) : Light(x, y, z, colour) {}

PointLight::~PointLight() {}