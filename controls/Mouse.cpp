#include "Mouse.h"

Mouse::Mouse()
{
	eventRecord = new std::vector<SDL_Event>();
}

float Mouse::getButtons(SDL_Event e)
{
	float z;

    if (e.type == SDL_MOUSEMOTION && e.button.button == SDL_BUTTON_LEFT) {
        if (e.motion.yrel > 0)
            return 0.01f;
        else if (e.motion.yrel < 0)
            return -0.01f;
    }

    eventRecord->push_back(e);

	return z;
}
