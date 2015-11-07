#include "Model.h"

Model::Model(float x, float y, float z, obj_data *objData) : Entity(x, y, z)
{
    name = objData->name;
    position.x = x;
    position.y = y;
    position.z = z;
    width = objData->width;
    height = objData->height;
    depth = objData->depth;
    positionVerts  = &objData->position;
    normalVerts    = &objData->normal;
    diffuseVerts   = &objData->diffuse;
    specularVerts  = &objData->specular;
    indexVerts     = &objData->positionIndex;
}

/*** set ***/

void Model::setScale(GLfloat scale)
{
    width *= scale;
    height *= scale;
    depth *= scale;
    this->scale = scale;
}

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

float Model::getWidth()
{
    return width;
}

float Model::getHeight()
{
    return height;
}

float Model::getDepth()
{
    return depth;
}

GLfloat * Model::getScale()
{
    return &scale;
}

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
