#include <GL/glut.h>
#include <vector>
#include <cmath>

float rotX = 0.0f;
float rotY = 0.0f;
int lastX = 0, lastY = 0; 
bool mouseLeftDown = false; 

const float a = 10.0f;
const float b = 28.0f;
const float c = 8.0f / 3.0f;
const float dt = 0.001f; 

struct Point3D {
    float x, y, z;
};
std::vector<Point3D> lorenzPoints;

// Initialize OpenGL settings
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    glEnable(GL_DEPTH_TEST); 


    float x = 0.001f, y = 0.0f, z = 0.0f; 
    for (int i = 0; i < 1000000; ++i) {

        float dx = a*(y - x);
        float dy = x*(b - z) - y;
        float dz = x*y - c * z;

        x += dx*dt;
        y += dy*dt;
        z += dz*dt;
        lorenzPoints.push_back({x, y, z});
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); 

    gluLookAt(0.0, 0.0, 100.0,  
              0.0, 0.0, 0.0,   
              0.0, 1.0, 0.0); 

    glRotatef(rotX, 1.0f, 0.0f, 0.0f); 
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);


    glColor3f(0.0f, 0.0f, 1.0f); 
    glBegin(GL_LINE_STRIP); 
    for (const auto& point : lorenzPoints) {
        glVertex3f(point.x, point.y, point.z);
    }
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 0.1, 1000.0); 
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseLeftDown = true;
            lastX = x;
            lastY = y;
        }
        else {
            mouseLeftDown = false;
        }
    }
}

void motion(int x, int y) {
    if (mouseLeftDown) {
        int deltaX = x - lastX;
        int deltaY = y - lastY;

        rotY += deltaX * 0.2f;
        rotX += deltaY * 0.2f;

        lastX = x;
        lastY = y;

        glutPostRedisplay(); 
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(800,500);
    glutCreateWindow("Lorenz Attractor");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);    
    glutMotionFunc(motion);  

    glutMainLoop(); 
    return 0;
}
