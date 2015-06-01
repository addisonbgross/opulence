#ifndef OPULENCE_CONTROLLERINTERFACE_H
#define OPULENCE_CONTROLLERINTERFACE_H

#include <iostream>
#include <SDL_stdinc.h>
#include <SDL_keyboard.h>
#include <glm/glm.hpp>

#define INCREASE 1
#define NOCHANGE 0
#define DECREASE -1

class Controller
{
    public:
        virtual ~Controller() {};
        virtual GLuint update() = 0;
};

class Keyboard : public Controller
{
public:
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    GLuint update() {
        if (currentKeyStates[SDL_SCANCODE_PERIOD ]) {
            return 1;

        } else if (currentKeyStates[SDL_SCANCODE_COMMA]) {
            return 1;

        } else if (currentKeyStates[SDL_SCANCODE_E]) {
            return 1;

        } else if (currentKeyStates[SDL_SCANCODE_R]) {
            return 1;

        } else {
            return 1;
        }
    }
};

#endif //OPULENCE_CONTROLLER_H
