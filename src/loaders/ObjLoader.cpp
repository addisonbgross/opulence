#include <glm/detail/type_vec.hpp>
#include <glm/detail/func_geometric.hpp>
#include "ObjLoader.h"

ObjLoader::ObjLoader() {}

std::vector<mtl_data> ObjLoader::importMtl(std::string filePath)
{
    std::string mtlPath = filePath.substr(0, filePath.find_last_of(".")) + ".mtl";

    std::ifstream fileStream(mtlPath, std::ios::in);
    if(!fileStream.is_open()) {
        std::cerr << "Could not read file [" << mtlPath << "] Does not exist." << std::endl;
    }

    std::string line = "";
    mtl_data mtl;
    mtl.name = "";
    std::vector<mtl_data> materials;
    GLfloat a, b, c;

    while(!fileStream.eof()) {
        std::getline(fileStream, line);

        if (line.c_str()[0] == 'n') {
            line = line.substr(7, line.length() - 1);
            if (mtl.name != "") {
                materials.push_back(mtl);
            }
            mtl.name = line;

        } else if (line.c_str()[1] == 'd') {
            line = line.substr(2, line.length() - 1);
            sscanf(line.c_str(), "%f %f %f ", &a, &b, &c);
            mtl.diffuse[0] = a;
            mtl.diffuse[1] = b;
            mtl.diffuse[2] = c;
        }
    }
    materials.push_back(mtl);

    return materials;
}

obj_data ObjLoader::import(std::string filePath)
{
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file [" << filePath << "] Does not exist." << std::endl;
    }

    obj_data objData;

    std::vector<mtl_data> mtlData = importMtl(filePath);


    std::string line = "";

    GLfloat a, b, c;
    GLuint  d, e, f,
            g, h, i;

    std::vector<GLfloat> tempNormals;

    while(!fileStream.eof()) {
        std::getline(fileStream, line);

        switch(line.c_str()[0]) {
            case 'v':
                line[0] = ' ';
                if (line.c_str()[1] == 'n') {
                    line[1] = ' ';
                    sscanf(line.c_str(), "%f %f %f ", &a, &b, &c);
                    tempNormals.push_back(a);
                    tempNormals.push_back(b);
                    tempNormals.push_back(c);
                    //std::cout << "vn " << a << " " << b << " " << c << std::endl;
                } else {
                    sscanf(line.c_str(), "%f %f %f ", &a, &b, &c);
                    objData.position.push_back(a);
                    objData.position.push_back(b);
                    objData.position.push_back(c);
                    objData.diffuse.push_back(0.5f);
                    objData.diffuse.push_back(0.5f);
                    objData.diffuse.push_back(0.5f);
                    objData.diffuse.push_back(1.0f);
                    //std::cout << "v " << a << " " << b << " " << c <<  std::endl;
                }
                break;

            case 'f':
                line[0] = ' ';
                sscanf(line.c_str(), "%i//%i %i//%i %i//%i ", &d, &e, &f, &g, &h, &i);
                objData.positionIndex.push_back(d - 1);
                objData.positionIndex.push_back(f - 1);
                objData.positionIndex.push_back(h - 1);
                objData.normalIndex.push_back(e - 1);
                objData.normalIndex.push_back(g - 1);
                objData.normalIndex.push_back(i - 1);
                //std::cout << "f " << d << "//" << e << " " << f << "//" << g << " " << h << "//" << i << std::endl;
                break;

            default:
                break;
        }
    }

    fileStream.close();

    objData.normal.resize( objData.positionIndex.size() );

    GLuint num, vertexIndex, normalIndex;
    for (num = 0; num < objData.positionIndex.size(); num++) {
        vertexIndex = (objData.positionIndex.at(num)) * 3;
        normalIndex = (objData.normalIndex.at(num)) * 3;
        //std::cout << "vert " << vertexIndex << " - norm " << normalIndex << std::endl;

        objData.normal.at(vertexIndex) = tempNormals.at(normalIndex);
        objData.normal.at(vertexIndex + 1) = tempNormals.at(normalIndex + 1);
        objData.normal.at(vertexIndex + 2) = tempNormals.at(normalIndex + 2);
        //std::cout << "n " << objData.normal[vertexIndex] <<
        //              " " << objData.normal[vertexIndex + 1] <<
       //               " " << objData.normal[vertexIndex + 2] << std::endl;
    }

    //objData.normal = tempNormals;

    return objData;
}
