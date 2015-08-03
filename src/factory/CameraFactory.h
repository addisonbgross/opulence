#ifndef OPULENCE_CAMERAFACTORY_H
#define OPULENCE_CAMERAFACTORY_H

#include <algorithm>
#include <vector>
#include <iostream>
#include "../entity/camera/Camera.h"

class CameraFactory {
private:
    std::vector<Camera *> activeCameras;
    Camera *mainCamera;

public:
    CameraFactory();
    ~CameraFactory();
    Camera * getCamera(int i);
    void setMainCamera(Camera *c);
    Camera * getMainCamera();

    template<typename T>
    T * makeCamera(T *cam)
    {
        cam = new T();
        activeCameras.push_back(cam);

        if (activeCameras.size() < 1) {
            setMainCamera(cam);
        }
        return cam;
    }

    template<typename T>
    T * makeCamera(glm::vec3 position, T *cam)
    {
        cam = new T(position.x, position.y, position.z);
        activeCameras.push_back(cam);

        if (activeCameras.size() < 1) {
            setMainCamera(cam);
        }

        return cam;
    }
};


#endif
