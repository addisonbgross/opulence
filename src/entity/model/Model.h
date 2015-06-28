#ifndef OPULENCE_MODEL_H
#define OPULENCE_MODEL_H

#include <vector>
#include <GL/gl.h>

#include "../../loaders/ObjLoader.h"

class Model
{
private:
    GLfloat x, y, z;

    std::vector<GLfloat> positionVerts;
    std::vector<GLfloat> normalVerts;
    std::vector<GLfloat> diffuseVerts;
    std::vector<GLfloat> specularVerts;
    std::vector<GLuint>  indexVerts;
    std::vector<GLuint>  normalIndexVerts;

public:
    Model();
    ~Model();
    Model(int x, int y, int z);
    Model(int x, int y, int z, obj_data objData);
    Model(int x, int y, int z, std::vector<GLfloat> v, std::vector<GLuint> i, std::vector<GLfloat> c);

    // set
    void setPositionVerts(std::vector<GLfloat> v);
    void setNormalVerts(std::vector<GLfloat> v);
    void setDiffuseVerts(std::vector<GLfloat> v);
    void setSpecularVerts(std::vector<GLfloat> v);
    void setIndexVerts(std::vector<GLuint> v);
    void setNormalIndexVerts(std::vector<GLuint> v);
    void setX(GLfloat x);
    void setY(GLfloat y);
    void setZ(GLfloat z);

    // get
    GLfloat * getPositionVerts();
    GLfloat * getNormalVerts();
    GLfloat * getDiffuseVerts();
    GLfloat * getSpecularVerts();
    GLuint * getIndexVerts();
    GLuint * getNormalIndexVerts();
    GLfloat getX();
    GLfloat getY();
    GLfloat getZ();
    unsigned long getNumPositionVerts();
    unsigned long getNumNormalVerts();
    unsigned long getNumDiffuseVerts();
    unsigned long getNumSpecularVerts();
    unsigned long getNumIndexVerts();
    unsigned long getNumNormalIndexVerts();
};

#endif //OPULENCE_MODEL_H
