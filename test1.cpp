#include<iostream>
#include<GL/glut.h>
#include<math.h>
#include<vector>

#define PI 3.14159265
#define deg *(PI/180)

#define size 10
double val=(double)size/20.0;
double outline_size=val*5;
using namespace std;

void quad_with_outline(vector<double>a,vector<double>b,vector<double>c,vector<double>d,vector<double>color){
    glBegin(GL_POLYGON);//rect outline
        glColor3f(color[0],color[1], color[2]);//color of outline of rect
        glVertex2f (a[0], a[1]);
        glVertex2f (b[0], b[1]);
        glVertex2f (c[0], c[1]);
        glVertex2f (d[0], d[1]);
    glEnd();
    glLineWidth(outline_size*3);//outline thickness
    glBegin(GL_LINE_LOOP);//rect outline
        glColor3f(0.0f, 0.0f, 0.0f);//color of outline of rect
        glVertex2f (a[0], a[1]);
        glVertex2f (b[0], b[1]);
        glVertex2f (c[0], c[1]);
        glVertex2f (d[0], d[1]);
    glEnd();
}

void displayHome(void){
    
    glClearColor(0.5, 0.5, 0.5,0.5); //Background Colour
    glClear(GL_COLOR_BUFFER_BIT);
    // triangle
    quad_with_outline(
        {val, 0.0},
        {val, -outline_size/7.5},
        {-val, -outline_size/7.5},
        {-val, 0.0},
        {1.0, 0.3, 0.3}
        );
    glFlush();
}

int main(int argc,char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(700, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab-3 Question-1");
    glutDisplayFunc(displayHome);
    glutMainLoop();
    return 0;
}