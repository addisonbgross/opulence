#ifndef OPULENCE_MODELFACTORY_H
#define OPULENCE_MODELFACTORY_H

#include "../entity/model/Model.h"
#include "../entity/animation/Animation.h"
#include "../loader/ObjLoader.h"
#include "../service/BufferCourier.h"
#include "../container/obj_data.h"

class ModelFactory {
private:
    BufferCourier *bufferCourier;

    // obj
    std::map<std::string, obj_data> objMap;
    std::string objSource = "";

public:
    Model * makeModel(float x, float y, float z, std::string name);
    Animation * makeAnimation(float x, float y, float z, std::string name);
    void setBufferCourier(BufferCourier *buff);

    void reportStats();

    //obj
    void setObjSource(std::string source);
    void addObj(std::string sourceFile);
};


#endif
