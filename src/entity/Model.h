#ifndef OPULENCE_MODEL_H
#define OPULENCE_MODEL_H

#include <vector>

#include <GL/gl.h>

class Model
{
private:
    int x, y, z;

    std::vector<GLfloat> positionVerts;
    std::vector<GLuint> indexVerts;

public:
    Model(int x, int y, int z);
    Model(int x, int y, int z, std::vector<GLfloat> v, std::vector<GLuint> i);
    // set
    void setPositionVerts(std::vector<GLfloat> v);
    void setIndexVerts(std::vector<GLuint> v);

    // get
    GLfloat * getPositionVerts();
    GLuint * getIndexVerts();
    unsigned long getNumPositionVerts();
    unsigned long getNumIndexVerts();
};

#endif //OPULENCE_MODEL_H
