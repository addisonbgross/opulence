#ifndef OPULENCE_MOUSE_H
#define OPULENCE_MOUSE_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <SDL.h>

class Mouse
{
public:
	std::vector<SDL_Event> *eventRecord;

    Mouse();
	float getButtons(SDL_Event e);
};

#endif // OPULENCE_MOUSE_H