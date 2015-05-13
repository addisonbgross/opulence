#include <glm/glm.hpp>

class Vertex
{
public:
    glm::vec3 position;
    glm::vec4 colour;

    void setPosition(glm::vec3 pos) {position = pos;}
    void setColour(glm::vec4 col) {colour = col;}
    glm::vec3 getPosition(glm::vec3 pos) {return position;}
    glm::vec4 getColour(glm::vec4 col) {return colour;}
};