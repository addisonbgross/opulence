#include "Model.h"

Model::Model(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Model::Model(int x, int y, int z, std::vector<GLfloat> v, std::vector<GLuint> i)
{
    this->x = x;
    this->y = y;
    this->z = z;
    positionVerts = v;
    indexVerts = i;
}

void Model::setPositionVerts(std::vector<GLfloat> v)
{
    positionVerts = v;
}

void Model::setIndexVerts(std::vector<GLuint> v)
{
    indexVerts = v;
}

GLfloat * Model::getPositionVerts()
{
    return positionVerts.data();
}

GLuint * Model::getIndexVerts()
{
    return indexVerts.data();
}

unsigned long Model::getNumPositionVerts()
{
    return positionVerts.size();
}

unsigned long Model::getNumIndexVerts()
{
    return indexVerts.size();
}