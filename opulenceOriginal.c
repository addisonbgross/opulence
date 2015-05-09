#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

//In this example, we will use a few IBO/VBO and a few VAO.
//We will use glDrawRangeElements to render some shapes.
//We will use a couple of simple shaders. GL 3.3 shaders.
//We will create a 3.3 forward context with freeGLUT.
//
//We are using GLEW to get function pointers.
//
//As for the VBO, we will use an interleaved vertex format.
//Vertex, texcoords and normals.
//Vertex and color.
//
//As for the IBO, we will use 16 bit unsigned integers.
//
//http://freeglut.sourceforge.net
//http://glew.sourceforge.net

#define BUFFER_OFFSET(i) ((void*)(i))

//Vertex, tex0
//
//SIZE : 4+4+4 +4+4 = 4*6 = 20 bytes
//It's better to make it multiple of 32
//32-20 = 12 bytes (of garbage should be added)
//12/4 = 3 floats should be added
struct TVertex_VT {
    float	x, y, z;
    float	s0, t0;
    float	padding[3];
};

//Vertex, normal, tex0
//
//SIZE : 4+4+4 +4+4+4 +4+4 = 4*8 = 32 bytes
struct TVertex_VNT {
    float	x, y, z;
    float	nx, ny, nz;
    float	s0, t0;
};

//Vertex, color
//
//SIZE : 4+4+4 +4 = 4*4 = 16 bytes
//It's better to make it multiple of 32
//32-16 = 16 bytes (of garbage should be added)
//16/4 = 4 floats should be added
struct TVertex_VC {
    float	x, y, z;
    unsigned int	color;
    float	padding[4];
};

//Globals

//A quad
GLushort	pindex_quad[6];
TVertex_VC	pvertex_quad[4];

//A triangle
GLushort		pindex_triangle[3];
TVertex_VNT		pvertex_triangle[3];

//1 VAO for the quad
//1 VAO for the triangle
GLuint VAOID[2];
//1 IBO for the quad (Index Buffer Object)
//1 IBO for the triangle
GLuint IBOID[2];
//1 VBO for the quad (Vertex Buffer Object)
//1 VBO for the triangle
GLuint VBOID[2];

//1 shader for the quad
//1 shader for the triangle
GLuint	ShaderProgram[2];
GLuint	VertexShader[2];
GLuint	FragmentShader[2];

//The location of ProjectionModelviewMatrix in the shaders
int ProjectionModelviewMatrix_Loc[2];

// loadFile - loads text file into char* fname
// allocates memory - so need to delete after use
// size of file returned in fSize
std::string loadFile(const char *fname) {
    std::ifstream file(fname);
    if(!file.is_open()) {
        std::cout << "Unable to open file " << fname << std::endl;
        exit(1);
    }

    std::stringstream fileData;
    fileData << file.rdbuf();
    file.close();

    return fileData.str();
}

// printShaderInfoLog
// From OpenGL Shading Language 3rd Edition, p215-216
// Display (hopefully) useful error messages if shader fails to compile
void printShaderInfoLog(GLint shader) {
    int infoLogLen = 0;
    int charsWritten = 0;
    GLchar *infoLog;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

    if (infoLogLen > 0) {
        infoLog = new GLchar[infoLogLen];
        // error check for fail to allocate memory omitted
        glGetShaderInfoLog(shader, infoLogLen, &charsWritten, infoLog);
        std::cout << "InfoLog : " << std::endl << infoLog << std::endl;
        delete [] infoLog;
    }
}

void InitGLStates() {
    glShadeModel(GL_SMOOTH);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glReadBuffer(GL_BACK);
    glDrawBuffer(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(true);
    glDisable(GL_STENCIL_TEST);
    glStencilMask(0xFFFFFFFF);
    glStencilFunc(GL_EQUAL, 0x00000000, 0x00000001);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClearDepth(1.0);
    glClearStencil(0);
    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_DITHER);
    glActiveTexture(GL_TEXTURE0);
}



int LoadShader(const char *pfilePath_vs, const char *pfilePath_fs,
               bool bindTexCoord0, bool bindNormal, bool bindColor,
               GLuint &shaderProgram, GLuint &vertexShader, GLuint &fragmentShader) {
    shaderProgram=0;
    vertexShader=0;
    fragmentShader=0;

    // load shaders & get length of each
    int vlen;
    int flen;
    std::string vertexShaderString = loadFile(pfilePath_vs);
    std::string fragmentShaderString = loadFile(pfilePath_fs);
    vlen = vertexShaderString.length();
    flen = fragmentShaderString.length();

    if(vertexShaderString.empty()) {
        return -1;
    }

    if(fragmentShaderString.empty()) {
        return -1;
    }

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char *vertexShaderCStr = vertexShaderString.c_str();
    const char *fragmentShaderCStr = fragmentShaderString.c_str();
    glShaderSource(vertexShader, 1, (const GLchar **)&vertexShaderCStr, &vlen);
    glShaderSource(fragmentShader, 1, (const GLchar **)&fragmentShaderCStr, &flen);

    GLint compiled;

    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
    if(compiled==false) {
        std::cout << "Vertex shader not compiled." << std::endl;
        printShaderInfoLog(vertexShader);

        glDeleteShader(vertexShader);
        vertexShader=0;
        glDeleteShader(fragmentShader);
        fragmentShader=0;

        return -1;
    }

    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
    if(compiled==false) {
        std::cout << "Fragment shader not compiled." << std::endl;
        printShaderInfoLog(fragmentShader);

        glDeleteShader(vertexShader);
        vertexShader=0;
        glDeleteShader(fragmentShader);
        fragmentShader=0;

        return -1;
    }

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glBindAttribLocation(shaderProgram, 0, "InVertex");

    if(bindTexCoord0)
        glBindAttribLocation(shaderProgram, 1, "InTexCoord0");

    if(bindNormal)
        glBindAttribLocation(shaderProgram, 2, "InNormal");

    if(bindColor)
        glBindAttribLocation(shaderProgram, 3, "InColor");

    glLinkProgram(shaderProgram);

    GLint IsLinked;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, (GLint *)&IsLinked);
    if(IsLinked==false) {
        std::cout << "Failed to link shader." << std::endl;

        GLint maxLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
        if(maxLength>0) {
            char *pLinkInfoLog = new char[maxLength];
            glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, pLinkInfoLog);
            std::cout << pLinkInfoLog << std::endl;
            delete [] pLinkInfoLog;
        }

        glDetachShader(shaderProgram, vertexShader);
        glDetachShader(shaderProgram, fragmentShader);
        glDeleteShader(vertexShader);
        vertexShader=0;
        glDeleteShader(fragmentShader);
        fragmentShader=0;
        glDeleteProgram(shaderProgram);
        shaderProgram=0;

        return -1;
    }

    return 1;		//Success
}

void CreateGeometry() {
    //A quad
    pvertex_quad[0].x = -0.8f;
    pvertex_quad[0].y = -0.5f;
    pvertex_quad[0].z = -0.9f;
    pvertex_quad[0].color = 0xFFFFFFFF;

    pvertex_quad[1].x = 0.0f;
    pvertex_quad[1].y = -0.5f;
    pvertex_quad[1].z = -0.9f;
    pvertex_quad[1].color = 0xFFFF0000;

    pvertex_quad[2].x = -0.8f;
    pvertex_quad[2].y = 0.5f;
    pvertex_quad[2].z = -0.9f;
    pvertex_quad[2].color = 0xFF00FF00;

    pvertex_quad[3].x = 0.0f;
    pvertex_quad[3].y = 0.5f;
    pvertex_quad[3].z = -0.9f;
    pvertex_quad[3].color = 0xFF0000FF;

    pindex_quad[0] = 0;
    pindex_quad[1] = 1;
    pindex_quad[2] = 2;
    pindex_quad[3] = 2;
    pindex_quad[4] = 1;
    pindex_quad[5] = 3;

    //The triangle
    pvertex_triangle[0].x = 0.0f;
    pvertex_triangle[0].y = 0.5f;
    pvertex_triangle[0].z = -1.0f;
    pvertex_triangle[0].nx = 0.0f;
    pvertex_triangle[0].ny = 0.0f;
    pvertex_triangle[0].nz = 1.0f;
    pvertex_triangle[0].s0 = 0.0f;
    pvertex_triangle[0].t0 = 0.0f;

    pvertex_triangle[1].x = 0.3f;
    pvertex_triangle[1].y = -0.5f;
    pvertex_triangle[1].z = -1.0f;
    pvertex_triangle[1].nx = 0.0f;
    pvertex_triangle[1].ny = 0.0f;
    pvertex_triangle[1].nz = 1.0f;
    pvertex_triangle[1].s0 = 1.0f;
    pvertex_triangle[1].t0 = 0.0f;

    pvertex_triangle[2].x = 0.8f;
    pvertex_triangle[2].y = 0.5f;
    pvertex_triangle[2].z = -1.0f;
    pvertex_triangle[2].nx = 0.0f;
    pvertex_triangle[2].ny = 0.0f;
    pvertex_triangle[2].nz = 1.0f;
    pvertex_triangle[2].s0 = 0.5f;
    pvertex_triangle[2].t0 = 1.0f;

    pindex_triangle[0] = 0;
    pindex_triangle[1] = 1;
    pindex_triangle[2] = 2;


    //Create the IBO for the quad
    //16 bit indices
    glGenBuffers(1, &IBOID[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOID[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLushort), pindex_quad, GL_STATIC_DRAW);

    GLenum error = glGetError();

    //Create the IBO for the triangle
    //16 bit indices
    //We could have actually made one big IBO for both the quad and triangle.
    glGenBuffers(1, &IBOID[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOID[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLushort), pindex_triangle, GL_STATIC_DRAW);

    error = glGetError();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    error = glGetError();

    //Create VBO for the quad
    glGenBuffers(1, &VBOID[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOID[0]);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(TVertex_VC), pvertex_quad, GL_STATIC_DRAW);

    error = glGetError();

    //Just testing
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Create VBO for the triangle
    glGenBuffers(1, &VBOID[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOID[1]);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(TVertex_VNT), pvertex_triangle, GL_STATIC_DRAW);

    //Just testing
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    error = glGetError();

    //VAO for the quad *********************
    glGenVertexArrays(1, &VAOID[0]);
    glBindVertexArray(VAOID[0]);

    //Bind the VBO and setup pointers for the VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBOID[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TVertex_VC), BUFFER_OFFSET(0));
    glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(TVertex_VC), BUFFER_OFFSET(sizeof(float)  *3));
    glEnableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    //Bind the IBO for the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOID[0]);

    //Second VAO setup *******************
    //This is for the triangle
    glGenVertexArrays(1, &VAOID[1]);
    glBindVertexArray(VAOID[1]);

    //Bind the VBO and setup pointers for the VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBOID[1]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TVertex_VNT), BUFFER_OFFSET(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TVertex_VNT), BUFFER_OFFSET(sizeof(float) * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(TVertex_VNT), BUFFER_OFFSET(sizeof(float) * 6));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glDisableVertexAttribArray(3);

    //Bind the IBO for the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOID[1]);

    //Just testing
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void display() {
    float projectionModelviewMatrix[16];

    //Just set it to identity matrix
    memset(projectionModelviewMatrix, 0, sizeof(float) * 16);
    projectionModelviewMatrix[0] = 1.0;
    projectionModelviewMatrix[5] = 1.0;
    projectionModelviewMatrix[10] = 1.0;
    projectionModelviewMatrix[15] = 1.0;

    //Clear all the buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //Bind the shader that we want to use
    glUseProgram(ShaderProgram[0]);
    //Setup all uniforms for your shader
    glUniformMatrix4fv(ProjectionModelviewMatrix_Loc[0], 1, false, projectionModelviewMatrix);
    //Bind the VAO
    glBindVertexArray(VAOID[0]);
    //At this point, we would bind textures but we aren't using textures in this example

    //Draw command
    //The first to last vertex is 0 to 3
    //6 indices will be used to render the 2 triangles. This make our quad.
    //The last parameter is the start address in the IBO => zero
    glDrawRangeElements(GL_TRIANGLES, 0, 3, 6, GL_UNSIGNED_SHORT, NULL);

    //Bind the shader that we want to use
    glUseProgram(ShaderProgram[1]);
    //Setup all uniforms for your shader
    glUniformMatrix4fv(ProjectionModelviewMatrix_Loc[1], 1, false, projectionModelviewMatrix);
    //Bind the VAO
    glBindVertexArray(VAOID[1]);
    //At this point, we would bind textures but we aren't using textures in this example

    //Draw command
    //The first to last vertex is 0 to 3
    //3 indices will be used to render 1 triangle.
    //The last parameter is the start address in the IBO => zero
    glDrawRangeElements(GL_TRIANGLES, 0, 3, 3, GL_UNSIGNED_SHORT, NULL);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

void ExitFunction(int value) {
    std::cout << "Exit called." << std::endl;

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glUseProgram(0);

    glDeleteBuffers(1, &IBOID[0]);
    glDeleteBuffers(1, &IBOID[1]);
    glDeleteBuffers(1, &VBOID[0]);
    glDeleteBuffers(1, &IBOID[1]);
    glDeleteVertexArrays(1, &VAOID[0]);
    glDeleteVertexArrays(1, &VAOID[1]);

    glDetachShader(ShaderProgram[0], VertexShader[0]);
    glDetachShader(ShaderProgram[0], FragmentShader[0]);
    glDeleteShader(VertexShader[0]);
    glDeleteShader(FragmentShader[0]);
    glDeleteProgram(ShaderProgram[0]);

    glDetachShader(ShaderProgram[1], VertexShader[1]);
    glDetachShader(ShaderProgram[1], FragmentShader[1]);
    glDeleteShader(VertexShader[1]);
    glDeleteShader(FragmentShader[1]);
    glDeleteProgram(ShaderProgram[1]);
}

int main (int argc, char* argv[]) {
    int i;
    int NumberOfExtensions;
    int OpenGLVersion[2];

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    //We want to make a GL 3.3 context
    glutInitContextVersion(3, 3);
    glutInitContextFlags(GLUT_CORE_PROFILE);
    glutInitWindowPosition(100, 50);
    glutInitWindowSize(600, 600);
    glutCreateWindow("GL 3.3 Test");

    //Currently, GLEW uses glGetString(GL_EXTENSIONS) which is not legal code
    //in GL 3.3, therefore GLEW would fail if we don't set this to TRUE.
    //GLEW will avoid looking for extensions and will just get function pointers for all GL functions.
    glewExperimental = true;
    GLenum err = glewInit();
    if(err != GLEW_OK) {
        //Problem: glewInit failed, something is seriously wrong.
        std::cout << "glewInit failed, aborting." << std::endl;
        exit(1);
    }

    //This is the new way for getting the GL version.
    //It returns integers. Much better than the old glGetString(GL_VERSION).
    glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
    glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);
    std::cout << "OpenGL major version = " << OpenGLVersion[0] << std::endl;
    std::cout << "OpenGL minor version = " << OpenGLVersion[1] << std::endl;

    //The old method to get the extension list is obsolete.
    //You must use glGetIntegerv and glGetStringi
    glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);

    //We don't need any extensions. Useless code.
    for(i = 0; i < NumberOfExtensions; i++) {
        const GLubyte *ccc = glGetStringi(GL_EXTENSIONS, i);
        //std::cout << "Extension[" << i << "] = " << glGetStringi(GL_EXTENSIONS, i) << std::endl;
    }
    std::cout << "Total OpenGL extensions = " << NumberOfExtensions << std::endl;

    InitGLStates();

    std::string prePath = "/home/champ/Git/crows/opulence/";

    if(LoadShader("/home/champ/Git/crows/opulence/Shader1.vert", "/home/champ/Git/crows/opulence/Shader1.frag", false, false, true, ShaderProgram[0], VertexShader[0], FragmentShader[0])==-1) {
        exit(1);
    } else {
        ProjectionModelviewMatrix_Loc[0] = glGetUniformLocation(ShaderProgram[0], "ProjectionModelviewMatrix");
    }

    if(LoadShader("/home/champ/Git/crows/opulence/Shader2.vert", "/home/champ/Git/crows/opulence/Shader2.frag", true, true, false, ShaderProgram[1], VertexShader[1], FragmentShader[1])==-1) {
        exit(1);
    } else {
        ProjectionModelviewMatrix_Loc[1] = glGetUniformLocation(ShaderProgram[1], "ProjectionModelviewMatrix");
    }

    CreateGeometry();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
