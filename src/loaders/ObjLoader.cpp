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

        } else if (line.c_str()[1] == 's') {
            line = line.substr(2, line.length() - 1);
            sscanf(line.c_str(), "%f %f %f ", &a, &b, &c);
            mtl.specular[0] = a;
            mtl.specular[1] = b;
            mtl.specular[2] = c;
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
    mtl_data currentMtl;

    std::string line = "";

    bool hasTextures = false;
    bool firstObject = true;
    GLuint newObject = 0;
    GLuint highFace = 0, highNormal = 0;
    GLint faceOffset = 0, normalOffset = 0;

    GLfloat a, b, c;
    GLuint  d, e, f,
            g, h, i,
            j, k, l;

    std::vector<GLfloat> tempNormals, tempPosition;
    GLuint count;
    while(!fileStream.eof()) {
        std::getline(fileStream, line);

        switch(line.c_str()[0]) {
            case 'g':
                newObject++;
                if (newObject == 2 && firstObject) {
                    firstObject = false;
                    newObject = 0;
                } else if (newObject == 2) {
                    newObject = 0;
                    faceOffset = highFace;
                    normalOffset = highNormal;
                    std::cout << "face " << faceOffset << std::endl;
                    std::cout << "normal " << normalOffset << std::endl;
                }

            case 'v':
                line[0] = ' ';
                if (line.c_str()[1] == 't') {
                    hasTextures = true;
                } else if (line.c_str()[1] == 'n') {
                    line[1] = ' ';
                    sscanf(line.c_str(), "%f %f %f ", &a, &b, &c);
                    tempNormals.push_back(a);
                    tempNormals.push_back(b);
                    tempNormals.push_back(c);
                } else {
                    sscanf(line.c_str(), "%f %f %f ", &a, &b, &c);
                    tempPosition.push_back(a);
                    tempPosition.push_back(b);
                    tempPosition.push_back(c);
                }
                break;

            case 'u':
                line = line.substr(7, line.size());
                count = 0;
                while (count < mtlData.size()) {
                    if (mtlData[count].name == line) {
                        currentMtl = mtlData[count];
                    }
                    ++count;
                }
                break;

            case 'f':
                line[0] = ' ';

                if (hasTextures) {
                    sscanf(line.c_str(), "%i/%i/%i %i/%i/%i %i/%i/%i ", &d, &j, &e, &f, &k, &g, &h, &l, &i);
                } else {
                    sscanf(line.c_str(), "%i//%i %i//%i %i//%i ", &d, &e, &f, &g, &h, &i);
                }

                checkHighMark(highFace, d, f, h);
                checkHighMark(highNormal, e, g, i);

                d -= faceOffset;
                f -= faceOffset;
                h -= faceOffset;

                e -= normalOffset;
                g -= normalOffset;
                i -= normalOffset;

                // diffuse colour
                pushThree(objData.diffuse, currentMtl.diffuse.x, currentMtl.diffuse.y, currentMtl.diffuse.z);
                objData.diffuse.push_back(1.0f);
                pushThree(objData.diffuse, currentMtl.diffuse.x, currentMtl.diffuse.y, currentMtl.diffuse.z);
                objData.diffuse.push_back(1.0f);
                pushThree(objData.diffuse, currentMtl.diffuse.x, currentMtl.diffuse.y, currentMtl.diffuse.z);
                objData.diffuse.push_back(1.0f);

                // specular colour
                pushThree(objData.specular, currentMtl.specular.x, currentMtl.specular.y, currentMtl.specular.z);
                objData.specular.push_back(1.0f);
                pushThree(objData.specular, currentMtl.specular.x, currentMtl.specular.y, currentMtl.specular.z);
                objData.specular.push_back(1.0f);
                pushThree(objData.specular, currentMtl.specular.x, currentMtl.specular.y, currentMtl.specular.z);
                objData.specular.push_back(1.0f);

                // position
                objData.position.push_back( tempPosition[3 * (d - 1)] );
                objData.position.push_back( tempPosition[3 * (d - 1) + 1] );
                objData.position.push_back( tempPosition[3 * (d - 1) + 2] );

                objData.position.push_back( tempPosition[3 * (f - 1)] );
                objData.position.push_back( tempPosition[3 * (f - 1) + 1] );
                objData.position.push_back( tempPosition[3 * (f - 1) + 2] );

                objData.position.push_back( tempPosition[3 * (h - 1)] );
                objData.position.push_back( tempPosition[3 * (h - 1) + 1] );
                objData.position.push_back( tempPosition[3 * (h - 1) + 2] );

                // normal
                objData.normal.push_back( tempNormals[3 * (e - 1)] );
                objData.normal.push_back( tempNormals[3 * (e - 1) + 1] );
                objData.normal.push_back( tempNormals[3 * (e - 1) + 2] );

                objData.normal.push_back( tempNormals[3 * (g - 1)] );
                objData.normal.push_back( tempNormals[3 * (g - 1) + 1] );
                objData.normal.push_back( tempNormals[3 * (g - 1) + 2] );

                objData.normal.push_back( tempNormals[3 * (i - 1)] );
                objData.normal.push_back( tempNormals[3 * (i - 1) + 1] );
                objData.normal.push_back( tempNormals[3 * (i - 1) + 2] );
                break;

            default:
                break;
        }
    }

    // create index buffer
    for (count = 0; count < objData.position.size(); ++count)
        objData.positionIndex.push_back(count);

    fileStream.close();

    return objData;
}

void ObjLoader::checkHighMark(GLuint high, GLuint a, GLuint b, GLuint c)
{
    if (a > high) {
        high = a;
    } else if (b > high) {
        high = b;
    } else if (c > high) {
        high = c;
    }
}

template <typename Type>
void ObjLoader::pushThree(std::vector<Type> &v, Type a, Type b, Type c)
{
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
}
