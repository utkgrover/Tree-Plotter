#include "helper.h"
#include<iostream>
#include<GL/glut.h>
#include<string>

void Helper::plotPoint(int x,int y){
    glVertex2i(x,y);
}

void Helper::clearScreen(){
    glClearColor(0,0,0,0); //sets the colour buffer to black
    glClear(GL_COLOR_BUFFER_BIT);//the background colour is now set to black (which was the default one too , so yeah..)

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1000,0,1000);

    glColor3f(1.0,1.0,1.0); 
    glPointSize(1);
}

void Helper::createWindow(int *argc, char **argv){
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB ); //we dont want indexed colours 
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH )- WINDOW_WIDTH)/ 2, (glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2 );
    glutCreateWindow("Display Window");
}