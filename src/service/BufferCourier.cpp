#include "BufferCourier.h"

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
    sendBuffers();
}

void BufferCourier::removeModel(GLuint id)
{
    activeModels.erase(activeModels.begin() + (double) id);
    update();
    sendBuffers();
}

void BufferCourier::sendBuffers()
{
    GLuint numModels = (GLuint) activeModels.size();

    std::cout << "# Active Models: " << numModels << std::endl;

    // enable variables within shader pipeline
    for (auto &i : bufferAttributes) {
        glEnableVertexAttribArray(bufferAttributes.at(i.first));
    }

    GLint i;
    for (i = 0; i < numModels; ++i) {
        Model *model = activeModels[i];

        // initialize buffer objects
        glGenBuffers(1, &ibo);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &nbo);
        glGenBuffers(1, &dcbo);
        glGenBuffers(1, &scbo);

        // set model position
        glm::vec3 modelPlace = glm::vec3(model->getX(),
                                         model->getY(),
                                         model->getZ());
        glUniform3fv(bufferUniforms.at("modelPosition"), 1, &modelPlace[0]);

        // set index data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     model->getNumIndexVerts() * sizeof(GLuint),
                     model->getIndexVerts(),
                     GL_STATIC_DRAW);

        numIndexVerts = model->getNumIndexVerts();

        // set vertex data
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,
                     model->getNumPositionVerts() * sizeof(GLfloat),
                     model->getPositionVerts(),
                     GL_STATIC_DRAW);
        glVertexAttribPointer(bufferAttributes.at("position"), 3, GL_FLOAT, GL_FALSE, 0, 0);

        // set normal data
        glBindBuffer(GL_ARRAY_BUFFER, nbo);
        glBufferData(GL_ARRAY_BUFFER,
                     model->getNumNormalVerts() * sizeof(GLfloat),
                     model->getNormalVerts(),
                     GL_STATIC_DRAW);
        glVertexAttribPointer(bufferAttributes.at("normal"), 3, GL_FLOAT, GL_FALSE, 0, 0);

        // set diffuse colour data
        glBindBuffer(GL_ARRAY_BUFFER, dcbo);
        glBufferData(GL_ARRAY_BUFFER,
                     model->getNumDiffuseVerts() * sizeof(GLfloat),
                     model->getDiffuseVerts(),
                     GL_STATIC_DRAW);
        glVertexAttribPointer(bufferAttributes.at("diffuse"), 4, GL_FLOAT, GL_FALSE, 0, 0);

        // set specular colour data
        glBindBuffer(GL_ARRAY_BUFFER, scbo);
        glBufferData(GL_ARRAY_BUFFER,
                     model->getNumSpecularVerts() * sizeof(GLfloat),
                     model->getSpecularVerts(),
                     GL_STATIC_DRAW);
        glVertexAttribPointer(bufferAttributes.at("specular"), 4, GL_FLOAT, GL_FALSE, 0, 0);

        render();
        update();
    }
}

void BufferCourier::update()
{
    glDeleteBuffers(1, &ibo);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &nbo);
    glDeleteBuffers(1, &dcbo);
    glDeleteBuffers(1, &scbo);
}

void BufferCourier::render()
{
    // set index data and render
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLES, numIndexVerts, GL_UNSIGNED_INT, 0);
}
