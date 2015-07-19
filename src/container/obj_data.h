#ifndef OPULENCE_OBJ_DATA_H
#define OPULENCE_OBJ_DATA_H

struct obj_data {
    std::vector<GLfloat> position;
    std::vector<GLfloat> normal;
    std::vector<GLfloat> diffuse;
    std::vector<GLfloat> specular;
    std::vector<GLuint>  positionIndex;
    std::vector<GLuint>  uvIndex;
    std::vector<GLuint>  normalIndex;
    std::vector<GLuint>  colourIndex;
};

struct mtl_data {
    std::string name;
    std::vector<GLuint> faces;
    glm::vec4 diffuse;
    glm::vec4 specular;
};

#endif
