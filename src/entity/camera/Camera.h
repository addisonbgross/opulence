#ifndef OPULENCE_CAMERA_H
#define OPULENCE_CAMERA_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:
    glm::vec3 *eye;    // position of camera's view point
    glm::vec3 *focus;  // target of view
    glm::vec3 *top;    // relative up direction of camera

public:
    Camera();
    ~Camera();

    // set
    void setEye(glm::vec3 *newEye);
    void setFocus(glm::vec3 *newFocus);
    void setTop(glm::vec3 *newTop);

    // get
    glm::vec3 *getEye();
    glm::vec3 *getFocus();
    glm::vec3 *getTop();
};

#endif //OPULENCE_CAMERA_H
