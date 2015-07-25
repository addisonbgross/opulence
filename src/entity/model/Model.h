#ifndef OPULENCE_MODEL_H
#define OPULENCE_MODEL_H

#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>

#include "../../container/obj_data.h"
#include "../Entity.h"

class Model : Entity {
private:
    GLuint id;

    std::vector<GLfloat> positionVerts;
    std::vector<GLfloat> normalVerts;
    std::vector<GLfloat> diffuseVerts;
    std::vector<GLfloat> specularVerts;
    std::vector<GLuint>  indexVerts;
    std::vector<GLuint>  normalIndexVerts;

public:
    GLuint positionBuffer,
            normalBuffer,
            diffuseBuffer,
            specularBuffer,
            indexBuffer;

    Model();
    ~Model();
    Model(float x, float y, float z);
    Model(float x, float y, float z, obj_data objData);
    Model(float x, float y, float z, std::vector<GLfloat> v, std::vector<GLuint> i, std::vector<GLfloat> c);

    // set
    void setPositionVerts(std::vector<GLfloat> v);
    void setNormalVerts(std::vector<GLfloat> v);
    void setDiffuseVerts(std::vector<GLfloat> v);
    void setSpecularVerts(std::vector<GLfloat> v);
    void setIndexVerts(std::vector<GLuint> v);
    void setNormalIndexVerts(std::vector<GLuint> v);
    void setId(GLuint id);
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
    GLuint getId();
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
