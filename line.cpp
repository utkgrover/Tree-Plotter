#include<stdio.h>
#include<iostream>
#include<GL/glut.h>
#include<math.h>
#include"helper.h"
#include"line.h"

const int WINDOW_WIDTH=500;
const int WINDOW_HEIGHT=500;
static int X1, Y1, X2, Y2;

void plotPoint(int x,int y){
    glVertex2i(x,y);
}

void correctAlignment(int *x1, int *y1, int *x2, int *y2){
    if(*y1>*y2){
        int temp = *x1;
        *x1=*x2;
        *x2=temp;

        temp = *y1;
        *y1=*y2;
        *y2=temp;
    }
}

int getSlopeType(int x1, int y1, int x2, int y2){
    if(x2==x1) return 1;

    double slope = ((double)(y2-y1))/(x2-x1);
    if(slope>=0 && slope<=1) return 0;
    else if(slope>1) return 1;
    else if(slope<0 && slope>=-1) return 3;
    else return 2;
}

void Line::drawLine(int x1, int y1, int x2, int y2){
    correctAlignment(&x1,&y1,&x2,&y2);
    int slopeType = getSlopeType(x1,y1,x2,y2);
    int temp;
    // printf("original x1 %d y1 %d x2 %d y2 %d slopetype %d\n", x1,y1,x2,y2,slopeType);
    switch(slopeType){
        case 1:
            temp = y2;
            y2 = x2-x1+y1;
            x2 = temp-y1+x1;
            break;
        case 3:
            x2 = 2*x1 -x2;
            break;
        case 2:
            temp= y2;
            y2 = x1-x2+y1;
            x2 = x1 + (temp-y1);
            break;
    }
    // printf("after x1 %d y1 %d x2 %d y2 %d\n", x1,y1,x2,y2);
    int dx= x2-x1;
    int dy= y2-y1;
    int d= 2*dy-dx;
    int inc_east=2*dy;
    int inc_northeast=2*(dy-dx);
    int x=0,y=0;

    glBegin(GL_POINTS);
    plotPoint(x+x1,y+y1);

    while(x+x1<x2){
        if(d<=0){
            //choose E
            d+=inc_east;
        }else{
            //choose NE
            d+=inc_northeast;
            y++;
        }
        x++;
        switch(slopeType){
            case 0:
                plotPoint(x1+x,y1+y);
                break;
            case 1:
                plotPoint(x1+y,y1+x);
                break;
            case 2:
                plotPoint(x1-y,y1+x);
                break;
            case 3:
                plotPoint(x1-x,y1+y);
                break;
        }
    }
    glEnd();
}



void Line::drawLine(int x1, int y1, int x2, int y2, int padding){
    correctAlignment(&x1,&y1,&x2,&y2);
    double len = sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
    int x_correction = (int)((x2-x1)*padding/len);
    int y_correction = (int)((y2-y1)*padding/len);
    Line::drawLine(x1+x_correction, y1+y_correction, x2 - x_correction, y2-y_correction);
}

void render(void);

/*int main()
{
    std::cin>>X1>>Y1>>X2>>Y2;
    char *title = "line";
    Helper::createWindow(1000,1000,title);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(render);
    glutMainLoop();
    return 0;
}*/

void render(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,WINDOW_WIDTH,0.0,WINDOW_HEIGHT);
    glColor3f(1.0,0.0,0.0);
    glPointSize(1);
    Line::drawLine(X1, Y1, X2, Y2);
    glFlush();
}

//refs
// 1 https://www.lighthouse3d.com/tutorials/glut-tutorial/initialization/
//2 https://www.youtube.com/watch?v=vdVEFW5jn7U&t=196s
