#ifndef OPULENCE_MODELFACTORY_H
#define OPULENCE_MODELFACTORY_H

// general
#include <sstream>

// opulence
#include "../loader/ObjLoader.h"
#include "../service/BufferCourier.h"
#include "../container/obj_data.h"

class ModelFactory {
private:
    BufferCourier *bufferCourier;

    // obj
    std::map<std::string, obj_data> objMap;
    obj_data blank;
    bool isBlankSet = false;
    std::string objSource = "";

public:
    Model * makeModel(float x, float y, float z, std::string name);
    Model * makeModel(float x, float y, float z, std::string name, float scale);
    Animation * makeAnimation(float x, float y, float z, std::string name);
    Animation * makeAnimation(float x, float y, float z, std::string name, float scale);
    void setBufferCourier(BufferCourier *buff);

    void reportStats();

    // remove
    void destroyModel(Model *model);
    void destroyAnimation(Animation *animation);

    // obj
    void setObjSource(std::string source);
    void addObj(std::string sourceFile);

    // get
    Model * getModel(std::string name);

    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
};


#endif
