#include "Courier.h"

Courier::Courier() { bufferAttributes= std::map<std::string, GLint>(); }

void Courier::addAttribute(std::string name, GLint attrib)
{
    bufferAttributes.insert({name, attrib});
}

void Courier::addUniform(std::string name, GLint unif)
{
    bufferUniforms.insert({name, unif});
}

GLint Courier::getAttribute(std::string name)
{
    return bufferAttributes.at(name);
}

GLint Courier::getUniform(std::string name)
{
    return bufferUniforms.at(name);
}

void Courier::addModel(Model *model)
{
    activeModels.push_back(model);
}

void Courier::sendBuffers()
{
    GLuint numModels = activeModels.size();

    GLuint i;
    for (i = 0; i < numModels; ++i) {
        Model *model = activeModels[i];
        GLuint numAttributes = bufferAttributes.size();

        // create VBO
        GLuint ibo, vbo, nbo, dcbo, scbo;
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
                     model->getNumColourVerts() * sizeof(GLfloat),
                     model->getColourVerts(),
                     GL_STATIC_DRAW);
        glVertexAttribPointer(bufferAttributes.at("diffuse"), 4, GL_FLOAT, GL_FALSE, 0, 0);

        // enable variables within shader pipeline
        for (auto& i : bufferAttributes) {
            glEnableVertexAttribArray(bufferAttributes.at(i.first));
        }

        // set index data and render
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glDrawElements(GL_TRIANGLES, model->getNumIndexVerts(), GL_UNSIGNED_INT, 0);

        // free shader variables
        for (auto& i : bufferAttributes) {
            glDisableVertexAttribArray(bufferAttributes.at(i.first));
        }
    }
}
