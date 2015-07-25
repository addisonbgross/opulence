#include "Model.h"

Model::Model() {}

Model::Model(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Model::~Model() {}

Model::Model(float x, float y, float z, obj_data objData)
{
    this->x = x;
    this->y = y;
    this->z = z;
    positionVerts  = objData.position;
    normalVerts    = objData.normal;
    diffuseVerts   = objData.diffuse;
    specularVerts  = objData.specular;
    indexVerts     = objData.positionIndex;
}

Model::Model(float x, float y, float z, std::vector<GLfloat> v, std::vector<GLuint> i, std::vector<GLfloat> c)
{
    this->x = x;
    this->y = y;
    this->z = z;
    positionVerts = v;
    diffuseVerts = c;
    indexVerts = i;
}

/*** setters ***/

void Model::setId(GLuint id)
{
    this->id = id;
}

void Model::setX(GLfloat x)
{
    this->x = x;
}

void Model::setY(GLfloat y)
{
    this->y = y;
}

void Model::setZ(GLfloat z)
{
    this->z = z;
}

void Model::setPositionVerts(std::vector<GLfloat> v)
{
    positionVerts = v;
}

void Model::setNormalVerts(std::vector<GLfloat> v)
{
    normalVerts = v;
}

void Model::setDiffuseVerts(std::vector<GLfloat> v)
{
    diffuseVerts = v;
}

void Model::setSpecularVerts(std::vector<GLfloat> v)
{
    specularVerts = v;
}

void Model::setIndexVerts(std::vector<GLuint> v)
{
    indexVerts = v;
}

void Model::setNormalIndexVerts(std::vector<GLuint> v)
{
    normalIndexVerts = v;
}

/*** getters ***/

GLfloat Model::getX()
{
    return this->x;
}

GLfloat Model::getY()
{
    return this->y;
}

GLfloat Model::getZ()
{
    return this->z;
}

GLfloat * Model::getPositionVerts()
{
    return positionVerts.data();
}

GLfloat * Model::getNormalVerts()
{
    return normalVerts.data();
}

GLfloat * Model::getDiffuseVerts()
{
    return diffuseVerts.data();
}

GLfloat * Model::getSpecularVerts()
{
    return specularVerts.data();
}

GLuint * Model::getIndexVerts()
{
    return indexVerts.data();
}

GLuint * Model::getNormalIndexVerts()
{
    return normalIndexVerts.data();
}

unsigned long Model::getNumPositionVerts()
{
    return positionVerts.size();
}

unsigned long Model::getNumNormalVerts()
{
    return normalVerts.size();
}

unsigned long Model::getNumDiffuseVerts()
{
    return diffuseVerts.size();
}

unsigned long Model::getNumSpecularVerts()
{
    return specularVerts.size();
}

unsigned long Model::getNumIndexVerts()
{
    return indexVerts.size();
}

unsigned long Model::getNumNormalIndexVerts()
{
    return normalIndexVerts.size();
}