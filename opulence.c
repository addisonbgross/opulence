#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glVertex3f(0.5f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("Lighthouse3D - GLUT Tutorial");

    // register callbacks
    glutDisplayFunc(renderScene);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 0;
}
