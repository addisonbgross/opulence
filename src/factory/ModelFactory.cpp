#include "ModelFactory.h"

void ModelFactory::setObjSource(std::string source)
{
    objSource = source;
}

void ModelFactory::addObj(std::string name)
{
    ObjLoader objLoader;
    objMap.insert(std::pair<std::string, obj_data>(name, objLoader.import(objSource + name + ".obj")));
}

Model * ModelFactory::makeModel(float x, float y, float z, std::string name)
{
    if (objMap.count(name) > 0) {
        Model *model = new Model(x, y, z, &objMap.at(name));
        activeModels.push_back(model);
        bufferCourier->addModel(activeModels.at(activeModels.size() - 1));
    } else {
        std::cout << "ERR: Could not find obj model -> " << name << ".obj" << std::endl;
    }
}

void ModelFactory::setBufferCourier(BufferCourier *buff)
{
    bufferCourier = buff;
}