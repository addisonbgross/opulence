#include "ModelFactory.h"

void ModelFactory::setObjSource(std::string source)
{
    objSource = source;
}

void ModelFactory::addObj(std::string name)
{
    if (objSource == "") {
        std::cout << "Cannot make the Model [" + name + "] - no objSource set! Try the setObjSource() function" << std::endl;
    } else {
        ObjLoader objLoader;
        objMap.insert(std::pair<std::string, obj_data>(name, objLoader.import(objSource + name + ".obj")));
    }
}

Model * ModelFactory::makeModel(float x, float y, float z, std::string name)
{
    Model *model = new Model(x, y, z, objMap.at(name));
    activeModels.push_back(model);
    bufferCourier->addModel(activeModels.at(activeModels.size() - 1));
}

void ModelFactory::setBufferCourier(BufferCourier *buff)
{
    bufferCourier = buff;
}