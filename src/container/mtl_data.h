#ifndef OPULENCE_MTL_DATA_H
#define OPULENCE_MTL_DATA_H

struct mtl_data {
    std::string name;
    std::vector<GLuint> faces;
    glm::vec4 diffuse;
    glm::vec4 specular;
};

#endif
