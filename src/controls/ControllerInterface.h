#ifndef OPULENCE_CONTROLLERINTERFACE_H
#define OPULENCE_CONTROLLERINTERFACE_H

#include <iostream>
#include <SDL_stdinc.h>
#include <SDL_keyboard.h>
#include <glm/glm.hpp>

class Controller
{
    public:
        virtual ~Controller() {};
        virtual glm::vec4 update() = 0;
};

class Keyboard : public Controller
{
public:
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    glm::vec4 red   = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 green = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    glm::vec4 blue  = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    glm::vec4 white = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec4 black = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    glm::vec4 update() {
        if (currentKeyStates[SDL_SCANCODE_Q ]) {
            return red;

        } else if (currentKeyStates[SDL_SCANCODE_W]) {
            return green;

        } else if (currentKeyStates[SDL_SCANCODE_E]) {
            return blue;

        } else if (currentKeyStates[SDL_SCANCODE_R]) {
            return white;

        } else {
            return black;
        }
    }
};

#endif //OPULENCE_CONTROLLER_H
