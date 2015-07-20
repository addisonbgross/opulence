#ifndef OPULENCE_CAMERAFACTORY_H
#define OPULENCE_CAMERAFACTORY_H

#include <algorithm>
#include <vector>
#include "../entity/camera/Camera.h"

class CameraFactory {
private:
    std::vector<Camera *> activeCameras;
    Camera *mainCamera;

public:
    CameraFactory();
    ~CameraFactory();
    Camera * makeCamera(glm::vec3 position);
    Camera * getCamera(int i);
    void setMainCamera(Camera *c);
    Camera * getMainCamera();
};


#endif //OPULENCE_CAMERAFACTORY_H
