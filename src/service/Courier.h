#ifndef OPULENCE_COURIER_H
#define OPULENCE_COURIER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>

#include "../entity/model/Model.h"

class Courier {
private:
    std::map<std::string, GLint> bufferAttributes;
    std::map<std::string, GLint> bufferUniforms;
    std::vector<Model *> activeModels;

public:
    Courier();
    ~Courier() = default;
    void addAttribute(std::string name, GLint attrib);
    void addUniform(std::string name, GLint unif);
    GLint getAttribute(std::string name);
    GLint getUniform(std::string name);
    void addModel(Model *model);
    void sendBuffers();
};

#endif //OPULENCE_COURIER_H
