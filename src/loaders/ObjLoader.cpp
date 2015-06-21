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

    std::vector<GLfloat> tempNormals, tempPosition, tempColour;
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

                if (d > highFace) {
                    highFace = d;
                } else if (f > highFace) {
                    highFace = f;
                } else if (h > highFace) {
                    highFace = h;
                }

                if (e > highNormal) {
                    highNormal = e;
                } else if (g > highNormal) {
                    highNormal = g;
                } else if (i > highNormal) {
                    highNormal = i;
                }

                d -= faceOffset;
                f -= faceOffset;
                h -= faceOffset;

                e -= normalOffset;
                g -= normalOffset;
                i -= normalOffset;


                // diffuse colour
                objData.diffuse.push_back(currentMtl.diffuse.x);
                objData.diffuse.push_back(currentMtl.diffuse.y);
                objData.diffuse.push_back(currentMtl.diffuse.z);
                objData.diffuse.push_back(1.0f);

                objData.diffuse.push_back(currentMtl.diffuse.x);
                objData.diffuse.push_back(currentMtl.diffuse.y);
                objData.diffuse.push_back(currentMtl.diffuse.z);
                objData.diffuse.push_back(1.0f);

                objData.diffuse.push_back(currentMtl.diffuse.x);
                objData.diffuse.push_back(currentMtl.diffuse.y);
                objData.diffuse.push_back(currentMtl.diffuse.z);
                objData.diffuse.push_back(1.0f);

                // specular colour
                objData.specular.push_back(currentMtl.specular.x);
                objData.specular.push_back(currentMtl.specular.y);
                objData.specular.push_back(currentMtl.specular.z);
                objData.specular.push_back(1.0f);

                objData.specular.push_back(currentMtl.specular.x);
                objData.specular.push_back(currentMtl.specular.y);
                objData.specular.push_back(currentMtl.specular.z);
                objData.specular.push_back(1.0f);

                objData.specular.push_back(currentMtl.specular.x);
                objData.specular.push_back(currentMtl.specular.y);
                objData.specular.push_back(currentMtl.specular.z);
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
    for (i = 0; i < objData.position.size(); ++i)
        objData.positionIndex.push_back(i);

    fileStream.close();

    return objData;
}
