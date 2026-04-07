#include<windows.h>
#include<GL/freeglut.h>
#include<math.h>

void circle(float cx , float cy , float r){
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 100; i++){
        float angle = 2 * 3.1416 * i / 100;
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    //Part's By Imran Salehin Sady

    //  SKY
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.6f, 0.7f);
    glVertex2f(-1, 0.5); //For bottom Left
    glVertex2f( 1, 0.5); //For bottom right
    glVertex2f(1,  1);   //For Up Right
    glVertex2f( -1, 1);  //For Up left
    glEnd();

    //Score
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1, 0.8);
    glVertex2f( 1, 0.8);
    glVertex2f(1,  1);
    glVertex2f( -1, 1);
    glEnd();

    //Cloud
    glColor3f(1.0f,1.0f,1.0f);
    circle(-0.7,0.65,0.11); //For Left Cloud Part
    circle(-0.8,0.65,0.09); //For Left Cloud Part
    circle(-0.6,0.65,0.08); //For Left Cloud Part


    circle(-0.3,0.65,0.1); //For Right Cloud Part
    circle(-0.2,0.65,0.09); //For Right Cloud Part
    circle(-0.1,0.65,0.08); //For Right Cloud Part
    glEnd();

    //Side Ground (RIGHT)
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.6f,0.2f);
    glVertex2f(0.8, -1);//Bottom left
    glVertex2f( 1, -1); //Bottom right
    glVertex2f(1,  0.5);//top right
    glVertex2f( 0.8, 0.5);//top left
    glEnd();

     //Side Ground (LEFT)
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.6f,0.2f);
    glVertex2f(-0.8, -1);
    glVertex2f( -1, -1);
    glVertex2f(-1,  0.5);
    glVertex2f( -0.8, 0.5);
    glEnd();

    //Road
    glBegin(GL_QUADS);
    glColor3f(0.18f,0.18f,0.20f);
    glVertex2f(-0.8, -1);
    glVertex2f( 0.8, -1.0);
    glVertex2f( 0.8, 0.5);
    glVertex2f(-0.8,  0.5);
    glEnd();

    //Road Border Left
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2d(-0.6,-1);
    glVertex2d(-0.6,0.5);
    glEnd();

    //Road Border Right
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2d(0.6,-1);
    glVertex2d(0.6,0.5);
    glEnd();

     //Road Border Middle
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2d(0.0,-1);
    glVertex2d(0.0,0.5);
    glEnd();

    //SUN part

    glColor3f(1.0f,0.8f,0.0f);
    circle(0.8,0.65,0.1);
    glEnd();

    //grass

    glColor3f(0.0f,0.5f,0.2f);
    circle(0.9,-0.5,0.05); //Right part
    circle(0.85,-0.6,0.04);
    circle(0.9,-0.7,0.05);
    circle(0.85,-0.8,0.04);

    circle(-0.9,-0.5,0.05);//Left part
    circle(-0.85,-0.6,0.04);
    circle(-0.9,-0.8,0.05);
    circle(-0.85,-0.9,0.04);

    //Tree
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f,0.5f,0.2f);
    glVertex2d(0.8,0.2);
    glVertex2d(1,0.2);
    glVertex2d(0.9,0.5);
    glEnd();


    glBegin(GL_QUADS); //Right side tree
    glColor3f(0.55f,0.35f,0.18f);
    glVertex2d(0.85,0.0);
    glVertex2d(0.95,0.0);
    glVertex2d(0.95,0.2);
    glVertex2d(0.85,0.2);

    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3f(0.0f,0.5f,0.2f);
    glVertex2d(-0.8,0.2);
    glVertex2d(-1,0.2);
    glVertex2d(-0.9,0.5);
    glEnd();

    glBegin(GL_QUADS); //Left side tree
    glColor3f(0.55f,0.35f,0.18f);
    glVertex2d(-0.85,0.0);
    glVertex2d(-0.95,0.0);
    glVertex2d(-0.95,0.2);
    glVertex2d(-0.85,0.2);


    glEnd();













    glFlush();
}

int main(int argc , char **argv){
    glutInit(&argc , argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,400);
    glutCreateWindow("Final Scene");

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
