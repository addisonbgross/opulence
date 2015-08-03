#include "Model.h"

Model::Model() {}

Model::~Model() {}

Model::Model(float x, float y, float z) : Entity()
{
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
}

Model::Model(float x, float y, float z, obj_data *objData) : Model(x, y, z)
{
    positionVerts  = &objData->position;
    normalVerts    = &objData->normal;
    diffuseVerts   = &objData->diffuse;
    specularVerts  = &objData->specular;
    indexVerts     = &objData->positionIndex;
}

/*** set ***/

void Model::setPositionVerts(std::vector<GLfloat> *v)
{
    positionVerts = v;
}

void Model::setNormalVerts(std::vector<GLfloat> *v)
{
    normalVerts = v;
}

void Model::setDiffuseVerts(std::vector<GLfloat> *v)
{
    diffuseVerts = v;
}

void Model::setSpecularVerts(std::vector<GLfloat> *v)
{
    specularVerts = v;
}

void Model::setIndexVerts(std::vector<GLuint> *v)
{
    indexVerts = v;
}

void Model::setNormalIndexVerts(std::vector<GLuint> *v)
{
    normalIndexVerts = v;
}

/*** get ***/

GLfloat * Model::getPositionVerts()
{
    return positionVerts->data();
}

GLfloat * Model::getNormalVerts()
{
    return normalVerts->data();
}

GLfloat * Model::getDiffuseVerts()
{
    return diffuseVerts->data();
}

GLfloat * Model::getSpecularVerts()
{
    return specularVerts->data();
}

GLuint * Model::getIndexVerts()
{
    return indexVerts->data();
}

GLuint * Model::getNormalIndexVerts()
{
    return normalIndexVerts->data();
}

unsigned long Model::getNumPositionVerts()
{
    return positionVerts->size();
}

unsigned long Model::getNumNormalVerts()
{
    return normalVerts->size();
}

unsigned long Model::getNumDiffuseVerts()
{
    return diffuseVerts->size();
}

unsigned long Model::getNumSpecularVerts()
{
    return specularVerts->size();
}

unsigned long Model::getNumIndexVerts()
{
    return indexVerts->size();
}

unsigned long Model::getNumNormalIndexVerts()
{
    return normalIndexVerts->size();
}
