#include "ObjLoader.h"

ObjLoader::ObjLoader() {}

ObjLoader::~ObjLoader() {}

/**
 * importMtl() - reads in each material from an obj model's mtl file
 *
 * @params filePath the path to the chosen model relative to opulence root folder
 * @return std::vector<mtl_data> contains each material from within the model
 */
std::vector<mtl_data> ObjLoader::importMtl(std::string filePath)
{
    // append file type to mtl file name
    std::string mtlPath = filePath.substr(0, filePath.find_last_of(".")) + ".mtl";

    // attempt to open file
    std::ifstream fileStream(mtlPath, std::ios::in);
    if(!fileStream.is_open()) {
        std::cerr << "Could not read file [" << mtlPath << "] Does not exist." << std::endl;
    }

    // current line in file
    std::string line = "";
    // current material being read
    mtl_data mtl;
    // name of current material
    mtl.name = "";
    // all materials in file
    std::vector<mtl_data> materials;
    GLfloat a, b, c;

    // read in mtl file
    while(!fileStream.eof()) {
        std::getline(fileStream, line);

        // material name
        if (line.c_str()[0] == 'n') {
            line = line.substr(7, line.length() - 1);
            if (mtl.name != "") {
                materials.push_back(mtl);
            }
            mtl.name = line;

        // diffuse colour
        } else if (line.c_str()[1] == 'd') {
            line = line.substr(2, line.length() - 1);
            sscanf(line.c_str(), "%f %f %f ", &a, &b, &c);
            mtl.diffuse[0] = a;
            mtl.diffuse[1] = b;
            mtl.diffuse[2] = c;

        // specular colour
        } else if (line.c_str()[1] == 's') {
            line = line.substr(2, line.length() - 1);
            sscanf(line.c_str(), "%f %f %f ", &a, &b, &c);
            mtl.specular[0] = a;
            mtl.specular[1] = b;
            mtl.specular[2] = c;
        }
    }
    materials.push_back(mtl);

    fileStream.close();

    return materials;
}

/**
 * import() - read in obj file and parse data into containers. opulence
 *            enjoys per-face lighting, meaning that vertices aren't shared
 *            between faces. This accounts for 3x the vertex data
 *
 * @params filePath path of obj file relative to the opulence root folder
 * @return obj_data all vertex and material data in obj file
 */
obj_data ObjLoader::import(std::string filePath)
{
    // attempt to open file
    std::ifstream fileStream(filePath, std::ios::in);
    if(!fileStream.is_open()) {
        std::cerr << "Could not read file [" << filePath << "] Does not exist." << std::endl;
    }

    // container for resulting data
    obj_data objData;

    // retrieve all mtl file data
    std::vector<mtl_data> mtlData = importMtl(filePath);
    mtl_data currentMtl;

    // current line in obj file
    std::string line = "";
    // flag to read in faces differently
    bool hasTextures = false;
    // flag to ensure face indices are correct
    bool firstObject = true;
    GLuint newObject = 0;
    // high water mark for face attribute indices
    GLuint highFace = 0, highTexture = 0, highNormal = 0;
    GLint faceOffset = 0, textureOffset = 0, normalOffset = 0;

    GLfloat a, b, c;
    GLuint  d, e, f,
            g, h, i,
            j, k, l;

    // temps for getting the dimensions of the obj model
    GLfloat minWidth,
          maxWidth,
          minHeight,
          maxHeight,
          minDepth,
          maxDepth;
    // temp containers for vertex data
    std::vector<GLfloat> tempPosition, tempUv, tempNormals;
    // generic counter for iteration
    GLuint count;

    // read
    while(!fileStream.eof()) {
        std::getline(fileStream, line);

        // first char of each line indicates data type
        switch(line.c_str()[0]) {
            // occurs twice before starting a new object within model
            case 'g':
                newObject++;
                if (newObject == 2 && firstObject) {
                    firstObject = false;
                    newObject = 0;

                // face indices are relative to each object within a model, but
                // the vector used stores the data for all objects. To ensure
                // the vector is filled correctly we must offest the face data
                // read in
                } else if (newObject == 2) {
                    newObject = 0;
                    faceOffset = highFace;
                    textureOffset = highTexture;
                    normalOffset = highNormal;
                }

            // vertex data
            case 'v':
                line[0] = ' ';

                // texture UV
                if (line.c_str()[1] == 't') {
                    hasTextures = true;
                    line[1] = ' ';
                    tempUv.push_back(a);
                    tempUv.push_back(b);
                    tempUv.push_back(c);

                // normal
                } else if (line.c_str()[1] == 'n') {
                    line[1] = ' ';
                    sscanf(line.c_str(), "%f %f %f ", &a, &b, &c);
                    tempNormals.push_back(a);
                    tempNormals.push_back(b);
                    tempNormals.push_back(c);

                // position
                } else {
                    sscanf(line.c_str(), "%f %f %f ", &a, &b, &c);
                    tempPosition.push_back(a);
                    tempPosition.push_back(b);
                    tempPosition.push_back(c);

                    if (a <= minWidth) {
                        minWidth = a;
                    } else if (a > maxWidth) {
                        maxWidth = a;
                    }

                    if (b <= minHeight) {
                        minHeight = b;
                    } else if (b > maxHeight) {
                        maxHeight = b;
                    }

                    if (c <= minDepth) {
                        minDepth = c;
                    } else if (c > maxDepth) {
                        maxDepth = c;
                    }
                }
                break;

            // set current material for faces
            case 'u':
                line = line.substr(7, line.size());
                count = 0;

                // find needed material from all names
                while (count < mtlData.size()) {
                    if (mtlData[count].name == line) {
                        currentMtl = mtlData[count];
                    }
                    ++count;
                }
                break;

            // face data. Three of each vertex data read in are created, this way
            // per-face lighting is acheived
            case 'f':
                line[0] = ' ';

                if (hasTextures) {
                    sscanf(line.c_str(), "%i/%i/%i %i/%i/%i %i/%i/%i ", &d, &j, &e, &f, &k, &g, &h, &l, &i);
                    /*                      d/j/e    f/k/g    h/l/i                                      */

                    // update face texture index high mark
                    checkHighMark(highTexture, j, k, i);
                    j -= textureOffset;
                    k -= textureOffset;
                    l -= textureOffset;

                    // texture mapping coordinates for a face
                    pushThree(objData.uvTexture,
                              tempUv[3 * (j - 1)],
                              tempUv[3 * (j - 1) + 1],
                              tempUv[3 * (j - 1) + 2]);

                    pushThree(objData.uvTexture,
                              tempUv[3 * (j - 1)],
                              tempUv[3 * (j - 1) + 1],
                              tempUv[3 * (j - 1) + 2]);

                    pushThree(objData.uvTexture,
                              tempUv[3 * (j - 1)],
                              tempUv[3 * (j - 1) + 1],
                              tempUv[3 * (j - 1) + 2]);
                } else {
                    sscanf(line.c_str(), "%i//%i %i//%i %i//%i ", &d, &e, &f, &g, &h, &i);
                    /*                     d//e   f//g   h//i                           */
                }

                // face normal and face index high marks
                checkHighMark(highFace, d, f, h);
                checkHighMark(highNormal, e, g, i);
                d -= faceOffset;
                f -= faceOffset;
                h -= faceOffset;
                e -= normalOffset;
                g -= normalOffset;
                i -= normalOffset;

                // diffuse colour for one face (transparency not implemented)
                pushThree(objData.diffuse,
                          currentMtl.diffuse.x,
                          currentMtl.diffuse.y,
                          currentMtl.diffuse.z);
                objData.diffuse.push_back(1.0f);

                pushThree(objData.diffuse,
                          currentMtl.diffuse.x,
                          currentMtl.diffuse.y,
                          currentMtl.diffuse.z);
                objData.diffuse.push_back(1.0f);

                pushThree(objData.diffuse,
                          currentMtl.diffuse.x,
                          currentMtl.diffuse.y,
                          currentMtl.diffuse.z);
                objData.diffuse.push_back(1.0f);

                // specular colour for one face (transparency not implemented)
                pushThree(objData.specular,
                          currentMtl.specular.x,
                          currentMtl.specular.y,
                          currentMtl.specular.z);
                objData.specular.push_back(1.0f);

                pushThree(objData.specular,
                          currentMtl.specular.x,
                          currentMtl.specular.y,
                          currentMtl.specular.z);
                objData.specular.push_back(1.0f);

                pushThree(objData.specular,
                          currentMtl.specular.x,
                          currentMtl.specular.y,
                          currentMtl.specular.z);
                objData.specular.push_back(1.0f);

                // position data for one face
                pushThree(objData.position,
                          tempPosition[3 * (d - 1)],
                          tempPosition[3 * (d - 1) + 1],
                          tempPosition[3 * (d - 1) + 2]);

                pushThree(objData.position,
                          tempPosition[3 * (f - 1)],
                          tempPosition[3 * (f - 1) + 1],
                          tempPosition[3 * (f - 1) + 2]);

                pushThree(objData.position,
                          tempPosition[3 * (h - 1)],
                          tempPosition[3 * (h - 1) + 1],
                          tempPosition[3 * (h - 1) + 2]);

                // normal data for one face
                pushThree(objData.normal,
                          tempNormals[3 * (e - 1)],
                          tempNormals[3 * (e - 1) + 1],
                          tempNormals[3 * (e - 1) + 2]);

                pushThree(objData.normal,
                          tempNormals[3 * (g - 1)],
                          tempNormals[3 * (g - 1) + 1],
                          tempNormals[3 * (g - 1) + 2]);

                pushThree(objData.normal,
                          tempNormals[3 * (i - 1)],
                          tempNormals[3 * (i - 1) + 1],
                          tempNormals[3 * (i - 1) + 2]);
                break;

            default:
                break;
        }
    }

    // derive model dimensions
    objData.width = maxWidth - minWidth;
    objData.height = maxHeight - minHeight;
    objData.depth = maxDepth - minDepth;

    // create index buffer
    for (count = 0; count < objData.position.size(); ++count)
        objData.positionIndex.push_back(count);

    fileStream.close();

    return objData;
}

/**
 * checkHighMark() - a high water mark is tested by three whatever
 *
 * @params &high,a,b,c compare three whatever to a current high water mark
 */
template <typename Type>
void ObjLoader::checkHighMark(Type &high, Type a, Type b, Type c)
{
    if (a > high) {
        high = a;
    } else if (b > high) {
        high = b;
    } else if (c > high) {
        high = c;
    }
}

/**
 * pushThree() - add three whatever to a vector containing whatever
 *
 * @params &v,a,b,c add three whatever to &v
 */
template <typename Type>
void ObjLoader::pushThree(std::vector<Type> &v, Type a, Type b, Type c)
{
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
}
