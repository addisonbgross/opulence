#ifndef OPULENCE_COURIER_H
#define OPULENCE_COURIER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>

#include "../entity/model/Model.h"

class BufferCourier {
private:
    std::map<std::string, GLint> bufferAttributes;
    std::map<std::string, GLint> bufferUniforms;
    std::vector<Model *> activeModels;
    GLuint numIndexVerts;

    // buffer objects
    GLuint ibo, vbo, nbo, dcbo, scbo;

public:
    BufferCourier();
    ~BufferCourier();
    void addAttribute(std::string name, GLint attrib);
    void addUniform(std::string name, GLint unif);
    GLint getAttribute(std::string name);
    GLint getUniform(std::string name);
    GLuint getNumModels();
    void addModel(Model *model);
    void removeModel(GLuint id);

    void sendBuffer(Model *model);
    void clearBuffer(Model *model);
    void render();
};

#endif //OPULENCE_COURIER_H
