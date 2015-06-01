#include "Model.h"

Model::Model(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Model::Model(int x, int y, int z, std::vector<GLfloat> v, std::vector<GLuint> i, std::vector<GLfloat> c)
{
    this->x = x;
    this->y = y;
    this->z = z;
    positionVerts = v;
    colourVerts = c;
    indexVerts = i;
}

/*** setters ***/

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

void Model::setColourVerts(std::vector<GLfloat> v)
{
    colourVerts = v;
}

void Model::setIndexVerts(std::vector<GLuint> v)
{
    indexVerts = v;
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

GLfloat * Model::getColourVerts()
{
    return colourVerts.data();
}

GLuint * Model::getIndexVerts()
{
    return indexVerts.data();
}

unsigned long Model::getNumPositionVerts()
{
    return positionVerts.size();
}

unsigned long Model::getNumColourVerts()
{
    return colourVerts.size();
}

unsigned long Model::getNumIndexVerts()
{
    return indexVerts.size();
}