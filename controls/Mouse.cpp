#include "Mouse.h"

Mouse::Mouse()
{
	eventRecord = new std::vector<SDL_Event>();
}

glm::vec3 * Mouse::getButtons(SDL_Event e, glm::vec3 *eye)
{
    if (e.type == SDL_MOUSEMOTION && e.button.button == SDL_BUTTON_LEFT) {
        if (e.motion.yrel > 0)
            eye->z += 0.05;
        else if (e.motion.yrel < 0)
            eye->z += -0.05f;
    }

    eventRecord->push_back(e);

    return eye;
}
