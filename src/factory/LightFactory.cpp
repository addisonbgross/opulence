#include "LightFactory.h"

LightFactory::LightFactory()
{
    ambientIntensity = 0.2;
    ambientColour = new glm::vec4(1.0, 1.0, 1.0, 1.0);
}

LightFactory::~LightFactory()
{
    delete ambientColour;
}

DirectionalLight * LightFactory::makeDirectionalLight(glm::vec4 *colour)
{
    directionalLight = new DirectionalLight(colour);
    return directionalLight;
}

DirectionalLight * LightFactory::makeDirectionalLight(glm::vec4 *colour, glm::vec3 *direction)
{
    directionalLight = new DirectionalLight(colour, direction);
    return directionalLight;
}

PointLight * LightFactory::makePointLight(float x, float y, float z)
{
    PointLight *pl = new PointLight(x, y, z, new glm::vec4(1.0, 1.0, 1.0, 1.0));
    pointLights.push_back( pl );
    return pl;
}

/*** setters ***/

void LightFactory::setAmbientColour(glm::vec4 *colour)
{
    ambientColour = colour;
}

void LightFactory::setAmbientIntensity(float i)
{
    ambientIntensity = glm::clamp( i, 0.0f, 1.0f );
}

void LightFactory::setDirectionalColour(glm::vec4 *colour)
{
    directionalLight->setColour( colour );
}

void LightFactory::setDirectionalIntensity(float i)
{
    directionalLight->setIntensity( glm::clamp( i, 0.0f, 1.0f ) );
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

float * LightFactory::getDirectionalIntensity()
{
    return directionalLight->getIntensity();
}

// PointLights
PointLight * LightFactory::getPointLights()
{
    return pointLights.at( 0 );
}

float *  LightFactory::getPointLightPositions()
{
    pointLightPositions.clear();

    for (auto point : pointLights) {
        pointLightPositions.push_back( point->position.x );
        pointLightPositions.push_back( point->position.y );
        pointLightPositions.push_back( point->position.z );
    }

    return pointLightPositions.data();
}

float * LightFactory::getPointLightLinearAttenuations()
{
    pointLightLinearAttenuations.clear();

    for (auto point : pointLights) {
        pointLightLinearAttenuations.push_back( *point->getLinearAttenuation() );
    }

    return pointLightLinearAttenuations.data();
}

float * LightFactory::getPointLightQuadradticAttenuations()
{
    pointLightQuadraticAttenuations.clear();

    for (auto point : pointLights) {
        pointLightQuadraticAttenuations.push_back( *point->getQuadraticAttenuation() );
    }

    return pointLightQuadraticAttenuations.data();
}
