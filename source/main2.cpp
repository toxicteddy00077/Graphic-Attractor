#include <GL/glut.h>
#include <vector>
#include <cmath>

float rotX = 0.0f;
float rotY = 0.0f;
int lastX = 0, lastY = 0; 
bool mouseLeftDown = false; 

const float a = 2.0f;
const float b = 1.7f;
const float c = 0.6f;
const float d=1.2f;

struct Point2D {
    float x, y;
};
std::vector<Point2D> cliffpoints;

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    glEnable(GL_DEPTH_TEST); 


    float x = 0.001f, y = 0.0f;
    for (int i = 0; i < 50000; ++i) {

        float dx =sin(a*y)+c*cos(a*x);
        float dy = sin(b*x)+d*cos(b*y);

        x = dx;
        y = dy;
        cliffpoints.push_back({x, y});
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity(); 

    glColor3f(0.0f, 1.0f, 1.0f); 
    glBegin(GL_POINTS); 
    for (const auto& point : cliffpoints) {
        glVertex2f(point.x , point.y ); 
    }
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-3.0, 3.0, -3.0, 3.0); 
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(800,500);
    glutCreateWindow("Cliford Attractor");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    // glutMenuStateFunc();

    glutMainLoop(); 
    return 0;
}
