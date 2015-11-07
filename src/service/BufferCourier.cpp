#include "BufferCourier.h"

BufferCourier::BufferCourier()
{
    bufferAttributes = std::map<std::string, GLint>();
}

BufferCourier::~BufferCourier() {}

/**
 * reportStats() - output current total amount of triangles in scene
 *                 and total amount of models in scene to std::cout
 */
void BufferCourier::reportStats()
{
    std::cout.imbue(std::locale(""));  // ensures that totals are comma separated numbers
    std::cout << "Total Triangles: " << totalTriangles << std::endl;
    std::cout << "Active Models: " << activeModels.size() << std::endl;
    std::cout << "Acitve Animations: " << activeAnimations.size() << std::endl;
}

/**
 * sendBuffer() - sends a model async to graphics card buffers
 *
 * @params *model the model which the out-going buffer data will derived
 */
void BufferCourier::sendBuffer(Model *model)
{
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

/**
 * clearBuffer() - removes a model's buffer data from the video card buffers
 *
 * @params *model the model which will be cleared
 */
void BufferCourier::clearBuffer(Model *model)
{
    glDeleteBuffers(1, &model->positionBuffer);
    glDeleteBuffers(1, &model->normalBuffer);
    glDeleteBuffers(1, &model->diffuseBuffer);
    glDeleteBuffers(1, &model->specularBuffer);
    glDeleteBuffers(1, &model->indexBuffer);
}

/**
 * render() - draws every model and animations frame buffer to the
 *            screen. Updates totalTriangles
 */
void BufferCourier::render()
{
    //Clear color, depth and stencil buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // enable GLSL attributes in pipeline
    for (auto &i : bufferAttributes) {
        glEnableVertexAttribArray(bufferAttributes.at(i.first));
    }

    // render every model accroding to their Cartesian coordinates
    totalTriangles = 0;
    GLuint numModels = (GLuint) activeModels.size();
    GLuint i;
    for (i = 0; i < numModels; ++i) {
        Model *model = activeModels[i];

        if (!model->hidden) {
            // set model position
            glm::vec3 modelPlace = glm::vec3(model->position.x,
                                             model->position.y,
                                             model->position.z);
            glUniform3fv(bufferUniforms.at("modelPosition"), 1, &modelPlace[0]);
            glUniform1fv(bufferUniforms.at("scale"), 1, model->getScale());
            glUniformMatrix4fv(bufferUniforms.at("orientation"), 1, GL_FALSE, model->getOrientation());

            // push vertex positions
            glBindBuffer(GL_ARRAY_BUFFER, model->positionBuffer);
            glVertexAttribPointer(bufferAttributes.at("position"), 3, GL_FLOAT, GL_FALSE, 0, 0);

            // push vertex normals
            glBindBuffer(GL_ARRAY_BUFFER, model->normalBuffer);
            glVertexAttribPointer(bufferAttributes.at("normal"), 3, GL_FLOAT, GL_FALSE, 0, 0);

            // push diffuse colour
            glBindBuffer(GL_ARRAY_BUFFER, model->diffuseBuffer);
            glVertexAttribPointer(bufferAttributes.at("diffuse"), 4, GL_FLOAT, GL_FALSE, 0, 0);

            // push specular colour
            glBindBuffer(GL_ARRAY_BUFFER, model->specularBuffer);
            glVertexAttribPointer(bufferAttributes.at("specular"), 4, GL_FLOAT, GL_FALSE, 0, 0);

            // push vertex indexes
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->indexBuffer);
            glDrawElements(GL_TRIANGLES, model->getNumIndexVerts(), GL_UNSIGNED_INT, 0);

            // update total triangles being drawn in scene
            totalTriangles += (model->getNumIndexVerts() / 3);
        }
    }

    // render the current frame of each animation
    GLuint numAnimations = (GLuint) activeAnimations.size();
    for (i = 0; i < numAnimations; ++i) {
        Model *model = activeAnimations.at(i)->getCurrentFrame();

        if (!model->hidden) {
            // set model position
            glm::vec3 modelPlace = glm::vec3(model->position.x,
                                             model->position.y,
                                             model->position.z);
            glUniform3fv(bufferUniforms.at("modelPosition"), 1, &modelPlace[0]);
            glUniform1fv(bufferUniforms.at("scale"), 1, model->getScale());
            glUniformMatrix4fv(bufferUniforms.at("orientation"), 1, GL_FALSE, activeAnimations.at(i)->getOrientation());

            // push vertex positions
            glBindBuffer(GL_ARRAY_BUFFER, model->positionBuffer);
            glVertexAttribPointer(bufferAttributes.at("position"), 3, GL_FLOAT, GL_FALSE, 0, 0);

            // push vertex normals
            glBindBuffer(GL_ARRAY_BUFFER, model->normalBuffer);
            glVertexAttribPointer(bufferAttributes.at("normal"), 3, GL_FLOAT, GL_FALSE, 0, 0);

            // push diffuse colour
            glBindBuffer(GL_ARRAY_BUFFER, model->diffuseBuffer);
            glVertexAttribPointer(bufferAttributes.at("diffuse"), 4, GL_FLOAT, GL_FALSE, 0, 0);

            // push specular colour
            glBindBuffer(GL_ARRAY_BUFFER, model->specularBuffer);
            glVertexAttribPointer(bufferAttributes.at("specular"), 4, GL_FLOAT, GL_FALSE, 0, 0);

            // push vertex indexes
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->indexBuffer);
            glDrawElements(GL_TRIANGLES, model->getNumIndexVerts(), GL_UNSIGNED_INT, 0);

            // update total triangles being drawn in scene
            totalTriangles += (model->getNumIndexVerts() / 3);
        }
    }
}

/**
 * addAttribute() - adds a GLSL attribute to collection
 *
 * @params name, attrib maps the name to the GLSL attribute
 */
void BufferCourier::addAttribute(std::string name, GLint attrib)
{
    bufferAttributes.insert({name, attrib});
}

/**
 * addUniform() - adds a GLSL uniform to collection
 *
 * @params name, unif maps the name to the GLSL uniform
 */
void BufferCourier::addUniform(std::string name, GLint unif)
{
    bufferUniforms.insert({name, unif});
}

/**
 * addModel() - adds an opulence model to collection
 *
 * @params *model being added
 */
void BufferCourier::addModel(Model *model)
{
    model->id = activeModels.size();

    activeModels.push_back(model);
    sendBuffer(model);
}

/**
 * addAnimation() - adds an opulence animation to collection
 *
 * @params *animation being added
 */
void BufferCourier::addAnimation(Animation *animation)
{
    animation->id = activeAnimations.size();

    activeAnimations.push_back(animation);

    for (int i = 0; i < animation->getNumFrames(); ++i) {
        sendBuffer(animation->getFrame(i));
    }
}

/**
 * removeModel() - removes model from the video card
 *
 * @params id the specific model which is to be deleted
 */
void BufferCourier::removeModel(int id)
{
    clearBuffer(activeModels[id]);
    activeModels.erase(activeModels.begin() + (double) id);
    activeModels.shrink_to_fit();

    for (int i = 0; i < activeModels.size(); ++i) {
        if (activeModels[i]->id > id) {
            activeModels[i]->id -= 1;
        }
    }
}

/**
 * removeAnimation() - removes animation from the video card
 *
 * @params animation the specific animation which is to be deleted
 */
void BufferCourier::removeAnimation(Animation *animation)
{
    for (int i = 0; i < animation->getNumFrames() - 1; ++i) {
        clearBuffer(animation->getFrame(i));
    }

    int id = animation->id;
    activeAnimations.erase(activeAnimations.begin() + (double) animation->id);
    activeAnimations.shrink_to_fit();

    // ensure all that the id's of all activeAnimations are also shrunk
    // to fit the vector correctly
    for (int i = 0; i < activeAnimations.size(); ++i) {
        if (activeAnimations[i]->id > id) {
            activeAnimations[i]->id -= 1;
        }
    }
}

/**
 * getAttribute() - gets the handle of the specified attribute in the video card
 *
 * @params name the name of the attribute in opulence
 * @return GLint handle of the attribute in the video card
 */
GLint BufferCourier::getAttribute(std::string name)
{
    return bufferAttributes.at(name);
}

/**
 * getUniform() - gets the handle of the specified uniform in the video card
 *
 * @params name the name of the uniform in opulence
 * @return GLint handle of the uniform in the video card
 */
GLint BufferCourier::getUniform(std::string name)
{
    return bufferUniforms.at(name);
}

/**
 * getNumModels() - total models in current opulence scene
 *
 * @return GLuint total models being rendered
 */
GLuint BufferCourier::getNumModels()
{
    return activeModels.size();
}

/**
 * getNumAnimations() - total animations in current opulence scene
 *
 * @return GLuint total animations being rendered
 */
GLuint BufferCourier::getNumAnimations()
{
    return activeAnimations.size();
}
