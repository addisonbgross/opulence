#include "ModelFactory.h"

void ModelFactory::setObjSource(std::string source)
{
    objSource = source;
}

void ModelFactory::addObj(std::string name)
{
    ObjLoader objLoader;
    obj_data obj = objLoader.import(objSource + name + ".obj");
    obj.name = name;
    objMap.insert(std::pair<std::string, obj_data>(name, obj));

    // create blank frame for animation hiding
    if (!isBlankSet) {
        isBlankSet = true;
        addObj("blank");
    }
}

Model * ModelFactory::makeModel(float x, float y, float z, std::string name)
{
    if (objMap.count(name) > 0) {
        Model *model = new Model(x, y, z, &objMap.at(name));
        bufferCourier->addModel(model);
        return model;
    } else {
        std::cout << "ERR: Could not find obj model -> " << name << ".obj" << std::endl;
    }
}

Model * ModelFactory::makeModel(float x, float y, float z, std::string name, float scale)
{
    if (objMap.count(name) > 0) {
        Model *model = new Model(x, y, z, &objMap.at(name));
        model->setScale(scale);
        bufferCourier->addModel(model);
        return model;
    } else {
        std::cout << "ERR: Could not find obj model -> " << name << ".obj" << std::endl;
    }
}

Animation * ModelFactory::makeAnimation(float x, float y, float z, std::string name)
{
    std::vector<Model*> *frames;
    std::string frameName;
    Model *model;
    if (objMap.count(name + "_0") > 0) {
        frames = new std::vector<Model*>();
        for (int i = 0; i < 6; ++i) {
            frameName = name + "_" + std::to_string(i);
            model = new Model(x, y, z, &objMap.at(frameName));
            frames->push_back(model);
        }
        frames->push_back(new Model(x, y, z, &objMap.at("blank")));
        Animation *animation = new Animation(x, y, z, frames);
        bufferCourier->addAnimation(animation);

        return animation;
    } else {
        std::cout << "ERR: Could not find obj animation -> " << name << ".obj" << std::endl;
    }
}

Animation * ModelFactory::makeAnimation(float x, float y, float z, std::string name, float scale)
{
    std::vector<Model*> *frames;
    std::string frameName;
    Model *model;
    if (objMap.count(name + "_0") > 0) {
        frames = new std::vector<Model*>();
        for (int i = 0; i < 6; ++i) {
            frameName = name + "_" + std::to_string(i);
            model = new Model(x, y, z, &objMap.at(frameName));
            model->setScale(scale);
            frames->push_back(model);
        }
        frames->push_back(new Model(x, y, z, &objMap.at("blank")));
        Animation *animation = new Animation(x, y, z, frames);
        bufferCourier->addAnimation(animation);

        return animation;
    } else {
        std::cout << "ERR: Could not find obj animation -> " << name << ".obj" << std::endl;
    }
}

void ModelFactory::setBufferCourier(BufferCourier *buff)
{
    bufferCourier = buff;
}

void ModelFactory::reportStats()
{
    std::cout << "----------------" << std::endl;
    std::cout << "Loaded Obj's: " << objMap.size() << std::endl;
    std::cout << "----------------" << std::endl;

    typedef std::map<std::string, obj_data>::const_iterator MapIterator;
    for (MapIterator iter = objMap.begin(); iter != objMap.end(); iter++) {
        std::cout << "* " << iter->first << std::endl;
    }
}

/*** remove ***/

void ModelFactory::destroyModel(Model *model)
{
    bufferCourier->removeModel(model->id);
}

void ModelFactory::destroyAnimation(Animation *animation)
{
    bufferCourier->removeAnimation(animation);
}