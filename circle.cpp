#include<iostream>
#include"helper.h"
#include<GL/glut.h>
#include"circle.h"

int CENTER_X=250,CENTER_Y=250, RADIUS=7;

void getAllPoints(int x,int y, int centerX, int centerY){
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
    Circle::drawCircle(CENTER_X, CENTER_Y, RADIUS);
    glFlush();
}
void idle(){}

/*int main(){
    char* title= "circle";
    Helper::createWindow(1000,1000,title);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
}*/