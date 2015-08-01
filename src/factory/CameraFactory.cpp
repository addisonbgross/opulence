#include "CameraFactory.h"

CameraFactory::CameraFactory() {}

CameraFactory::~CameraFactory() {}

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