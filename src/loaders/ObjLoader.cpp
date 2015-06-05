#include <glm/detail/type_vec.hpp>
#include "ObjLoader.h"

ObjLoader::ObjLoader() {}

obj_data ObjLoader::import(const char *filePath)
{
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file [" << filePath << "] Does not exist." << std::endl;
    }

    obj_data objData;

    std::string line = "";
    std::vector<GLfloat> positionVerts;
    std::vector<GLfloat> normalVerts;
    std::vector<GLfloat> colourVerts;
    std::vector<GLuint>  indexVerts;

    GLfloat a, b, c;
    GLuint  d, e, f;
    while(!fileStream.eof()) {
        std::getline(fileStream, line);

        switch(line.c_str()[0]) {
            case 'v':
                line[0] = ' ';
                if (line.c_str()[1] == 'n') {
                    std::cout << line.c_str() << std::endl;
                    line[1] = ' ';
                    sscanf(line.c_str(), "%f %f %f ", &a, &b, &c);
                    normalVerts.push_back(a);
                    normalVerts.push_back(b);
                    normalVerts.push_back(c);
                    std::cout << "vn " <<  a << " " << b << " " << c << std::endl;
                } else {
                    sscanf(line.c_str(), "%f %f %f ", &a, &b, &c);
                    positionVerts.push_back(a);
                    positionVerts.push_back(b);
                    positionVerts.push_back(c);
                    colourVerts.push_back(0.5f);
                    colourVerts.push_back(0.5f);
                    colourVerts.push_back(0.5f);
                    colourVerts.push_back(1.0f);
                    //std::cout << "v " <<  a << " " << b << " " << c << std::endl;
                }
                break;

            case 'f':
                line[0] = ' ';
                sscanf(line.c_str(), "%i %i %i ", &d, &e, &f);
                indexVerts.push_back(d - 1);
                indexVerts.push_back(e - 1);
                indexVerts.push_back(f - 1);
                break;

            default:
                break;
        }
    }
    objData.position = positionVerts;
    objData.normal   = normalVerts;
    objData.colour   = colourVerts;
    objData.index    = indexVerts;

    fileStream.close();

    return objData;
}
