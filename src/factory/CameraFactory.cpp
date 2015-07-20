#include "CameraFactory.h"

CameraFactory::CameraFactory() {}

CameraFactory::~CameraFactory() {}

Camera * CameraFactory::makeCamera(glm::vec3 position)
{
    Camera *newCamera = new Camera(position.x,
                                   position.y,
                                   position.z);
    activeCameras.push_back(newCamera);

    if (activeCameras.size() < 1) {
        setMainCamera(newCamera);
    }

    return newCamera;
}

Camera * CameraFactory::getCamera(int i)
{
    return activeCameras.at(i);
}

void CameraFactory::setMainCamera(Camera *c)
{
    mainCamera = c;
}

Camera * CameraFactory::getMainCamera()
{
    return activeCameras.at(0);
}