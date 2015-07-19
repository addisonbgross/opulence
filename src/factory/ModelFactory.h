#ifndef OPULENCE_MODELFACTORY_H
#define OPULENCE_MODELFACTORY_H

#include "../entity/model/Model.h"
#include "../loaders/ObjLoader.h"
#include "../service/BufferCourier.h"
#include "../container/obj_data.h"

class ModelFactory {
private:
    std::vector<Model *> activeModels;
    BufferCourier *bufferCourier;

    // obj
    std::map<std::string, obj_data> objMap;
    std::string objSource = "noSourceSet";

public:
    Model* makeModel(float x, float y, float z, std::string name);
    void setBufferCourier(BufferCourier *buff);

    //obj
    void setObjSource(std::string source);
    void addObj(std::string sourceFile);
};


#endif
