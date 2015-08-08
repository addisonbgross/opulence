#ifndef OPULENCE_COURIER_H
#define OPULENCE_COURIER_H

// general
#include <map>
#include <typeinfo>

// opulence
#include "../entity/model/Model.h"
#include "../entity/animation/Animation.h"
#include "../loader/ShaderLoader.h"

/**
 * BufferCourier - transfers data to and from video card
 */
class BufferCourier {
private:
    std::map<std::string, GLint> bufferAttributes;  // maps names to GLSL attributes
    std::map<std::string, GLint> bufferUniforms;    // maps names to GLSL uniforms
    std::vector<Model *> activeModels;              // all currently existing models
    std::vector<Animation *> activeAnimations;      // all currently existing animations
    int totalTriangles;                             // sum of all triangles from all models

public:
    BufferCourier();
    ~BufferCourier();
    void reportStats();                                 // print # triangles and # models
    void sendBuffer(Model *model);                      // send buffers async to video card
    void clearBuffer(Model *model);                     // remove handles related to model
    void render();                                      // draw to current frame buffer

    // add
    void addAttribute(std::string name, GLint attrib);  // add to active GLSL attributes
    void addUniform(std::string name, GLint unif);      // add to active GLSL uniform
    void addModel(Model *model);                        // add model to buffer system
    void addAnimation(Animation *animation);            // add animation to buffer system

    // remove
    void removeModel(GLuint id);                        // remove model from buffer system

    // get
    GLint getAttribute(std::string name);
    GLint getUniform(std::string name);
    GLuint getNumModels();
    GLuint getNumAnimations();
};

#endif
