#include <SDL_syswm.h>
#include "BufferCourier.h"
#include "GLManager.h"

BufferCourier::BufferCourier()
{
    bufferAttributes = std::map<std::string, GLint>();
}

BufferCourier::~BufferCourier() {}

void BufferCourier::addAttribute(std::string name, GLint attrib)
{
    bufferAttributes.insert({name, attrib});
}

void BufferCourier::addUniform(std::string name, GLint unif)
{
    bufferUniforms.insert({name, unif});
}

GLint BufferCourier::getAttribute(std::string name)
{
    return bufferAttributes.at(name);
}

GLint BufferCourier::getUniform(std::string name)
{
    return bufferUniforms.at(name);
}

GLuint BufferCourier::getNumModels()
{
    return activeModels.size();
}

void BufferCourier::addModel(Model *model)
{
    model->setId((GLuint) activeModels.size());
    activeModels.push_back(model);
    sendBuffer(model);
}

void BufferCourier::removeModel(GLuint id)
{
    activeModels.erase(activeModels.begin() + (double) id);
    clearBuffer(activeModels[id]);
}

void BufferCourier::sendBuffer(Model *model)
{
    std::cout << "# Active Models: " << activeModels.size() << std::endl;

    // initialize buffer objects
    glGenBuffers(1, &model->indexBuffer);
    glGenBuffers(1, &model->positionBuffer);
    glGenBuffers(1, &model->normalBuffer);
    glGenBuffers(1, &model->diffuseBuffer);
    glGenBuffers(1, &model->specularBuffer);

    // set index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 model->getNumIndexVerts() * sizeof(GLuint),
                 model->getIndexVerts(),
                 GL_STATIC_DRAW);

    // set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, model->positionBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 model->getNumPositionVerts() * sizeof(GLfloat),
                 model->getPositionVerts(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(bufferAttributes.at("position"), 3, GL_FLOAT, GL_FALSE, 0, 0);

    // set normal data
    glBindBuffer(GL_ARRAY_BUFFER, model->normalBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 model->getNumNormalVerts() * sizeof(GLfloat),
                 model->getNormalVerts(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(bufferAttributes.at("normal"), 3, GL_FLOAT, GL_FALSE, 0, 0);

    // set diffuse colour data
    glBindBuffer(GL_ARRAY_BUFFER, model->diffuseBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 model->getNumDiffuseVerts() * sizeof(GLfloat),
                 model->getDiffuseVerts(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(bufferAttributes.at("diffuse"), 4, GL_FLOAT, GL_FALSE, 0, 0);

    // set specular colour data
    glBindBuffer(GL_ARRAY_BUFFER, model->specularBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 model->getNumSpecularVerts() * sizeof(GLfloat),
                 model->getSpecularVerts(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(bufferAttributes.at("specular"), 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void BufferCourier::clearBuffer(Model *model)
{
    glDeleteBuffers(1, &model->positionBuffer);
    glDeleteBuffers(1, &model->normalBuffer);
    glDeleteBuffers(1, &model->diffuseBuffer);
    glDeleteBuffers(1, &model->specularBuffer);
    glDeleteBuffers(1, &model->indexBuffer);
}

void BufferCourier::render()
{
    //Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // set index data and render
    GLuint numModels = (GLuint) activeModels.size();

    // enable variables within shader pipeline
    for (auto &i : bufferAttributes) {
        glEnableVertexAttribArray(bufferAttributes.at(i.first));
    }

    GLuint i;
    for (i = 0; i < numModels; ++i) {
        Model *model = activeModels[i];

        // set model position
        glm::vec3 modelPlace = glm::vec3(model->getX(),
                                         model->getY(),
                                         model->getZ());
        glUniform3fv(bufferUniforms.at("modelPosition"), 1, &modelPlace[0]);

        glBindBuffer(GL_ARRAY_BUFFER, model->positionBuffer);
        glVertexAttribPointer(bufferAttributes.at("position"), 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, model->normalBuffer);
        glVertexAttribPointer(bufferAttributes.at("normal"), 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, model->diffuseBuffer);
        glVertexAttribPointer(bufferAttributes.at("diffuse"), 4, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, model->specularBuffer);
        glVertexAttribPointer(bufferAttributes.at("specular"), 4, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->indexBuffer);
        glDrawElements(GL_TRIANGLES, (GLsizei) model->getNumIndexVerts(), GL_UNSIGNED_INT, 0);
    }
}
