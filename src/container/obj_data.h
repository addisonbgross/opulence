#ifndef OPULENCE_OBJ_DATA_H
#define OPULENCE_OBJ_DATA_H

#include <iostream>
#include <glm/glm.hpp>

struct obj_data {
    std::vector<GLfloat> position;
    std::vector<GLfloat> normal;
    std::vector<GLfloat> diffuse;
    std::vector<GLfloat> specular;
    std::vector<GLfloat> uvTexture;
    std::vector<GLuint>  positionIndex;
    std::vector<GLuint>  normalIndex;
    std::vector<GLuint>  colourIndex;
    std::vector<GLuint>  textureIndex;
};

#endif
