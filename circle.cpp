#include<iostream>
#include"helper.h"
#include<GL/glut.h>
#include"circle.h"

int center_x=250,center_y=250, cradius=7;

void Circle::getAllPoints(int x,int y, int centerX, int centerY){
    Helper::plotPoint(x+centerX, y+centerY);
    Helper::plotPoint(-x+centerX, y+centerY);
    Helper::plotPoint(x+centerX, -y+centerY);
    Helper::plotPoint(-x+centerX, -y+centerY);
    Helper::plotPoint(y+centerX, x+centerY);
    Helper::plotPoint(-y+centerX, x+centerY);
    Helper::plotPoint(y+centerX, -x+centerY);
    Helper::plotPoint(-y+centerX, -x+centerY);
}

void Circle::drawCircle(int centerX, int centerY, int radius){
    int x=0,y=radius;
    int decision = 1 - radius;
    int deltaE = 3;
    int deltaSE = -2*radius + 5;

    glBegin(GL_POINTS);
    getAllPoints(x,y,centerX, centerY);

    while(y>x){
        if(decision<0){//take the upper point(E)
            decision+=deltaE;
            deltaE+=2;
            deltaSE+=2;
        }else{//take the lower point(SE)
            decision+=deltaSE;
            deltaE+=2;
            deltaSE+=4;
            y--;
        }
        x++;
        getAllPoints(x,y, centerX, centerY);
    }
    glEnd();
}

void display(void){
    Helper::clearScreen();
    Circle circle;
    circle.drawCircle(center_x, center_y, cradius);
    glFlush();
}

/**
 * @brief 
 * This function is used to take input from the user, generate a tree and display it on a window using OpenGL
 * @param argc Pointer to total number of arguments
 * @param argv The actual arguments to be passed to the function
 */
void Circle::initCircle(int *argc,char** argv){

    std::cout<<"Enter the coordinates of the center :"<<std::endl;
    std::cin>>center_x>>center_y;
    std::cout<<"Enter the radius of the circle :"<<std::endl;
    std::cin>>cradius;

    Helper::createWindow(argc,argv);
    
    glutDisplayFunc(display);
    // glutIdleFunc(idle);
    glutMainLoop();
}