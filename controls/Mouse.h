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
	glm::vec3 *getButtons(SDL_Event e, glm::vec3 *eye);
};

#endif // OPULENCE_MOUSE_H