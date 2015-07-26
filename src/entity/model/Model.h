#ifndef OPULENCE_MODEL_H
#define OPULENCE_MODEL_H

#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>

#include "../../container/obj_data.h"
#include "../Entity.h"

class Model : public Entity {
private:
    std::vector<GLfloat> *positionVerts;
    std::vector<GLfloat> *normalVerts;
    std::vector<GLfloat> *diffuseVerts;
    std::vector<GLfloat> *specularVerts;
    std::vector<GLuint>  *indexVerts;
    std::vector<GLuint>  *normalIndexVerts;

public:
    GLuint  positionBuffer,
            normalBuffer,
            diffuseBuffer,
            specularBuffer,
            indexBuffer;

    Model();
    ~Model();
    Model(float x, float y, float z);
    Model(float x, float y, float z, obj_data *objData);

    // set
    void setPositionVerts(std::vector<GLfloat> *v);
    void setNormalVerts(std::vector<GLfloat> *v);
    void setDiffuseVerts(std::vector<GLfloat> *v);
    void setSpecularVerts(std::vector<GLfloat> *v);
    void setIndexVerts(std::vector<GLuint> *v);
    void setNormalIndexVerts(std::vector<GLuint> *v);

    // get
    GLfloat * getPositionVerts();
    GLfloat * getNormalVerts();
    GLfloat * getDiffuseVerts();
    GLfloat * getSpecularVerts();
    GLuint * getIndexVerts();
    GLuint * getNormalIndexVerts();
    unsigned long getNumPositionVerts();
    unsigned long getNumNormalVerts();
    unsigned long getNumDiffuseVerts();
    unsigned long getNumSpecularVerts();
    unsigned long getNumIndexVerts();
    unsigned long getNumNormalIndexVerts();
};

#endif
