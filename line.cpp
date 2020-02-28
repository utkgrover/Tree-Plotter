#include<iostream>
#include<GL/glut.h>
#include<math.h>
#include"helper.h"
#include"line.h"

static int X1, Y1, X2, Y2;

/**
 * @brief This function ensures that the 1st point is always below the 2nd point 
 * because the Bresenham algorithm starts drawing from the lower point
 * 
 * @param x1 The X coordinate of 1st point
 * @param y1 The Y coordinate of 1st point
 * @param x2 The X coordinate of 2nd point
 * @param y2 The Y coordinate of 2nd point
 */
void Line::correctAlignment(int *x1, int *y1, int *x2, int *y2){
    if(*y1>*y2){
        int temp = *x1;
        *x1=*x2;
        *x2=temp;

        temp = *y1;
        *y1=*y2;
        *y2=temp;
    }
}

/**
 * @brief Get the slope category of the line based on it's slope
 * 
 * @param x1 The X coordinate of 1st point
 * @param y1 The Y coordinate of 1st point
 * @param x2 The X coordinate of 2nd point
 * @param y2 The Y coordinate of 2nd point
 * @return int 
 * 0 - slope lies between 0 and 1
 * 1 - slope lies between 1 and infinity
 * 2 - slope lies between minus infinity and -1
 * 3 - slope lies between -1 and 0
 */
int Line::getSlopeType(int x1, int y1, int x2, int y2){
    if(x2==x1) return 1;

    double slope = ((double)(y2-y1))/(x2-x1);
    if(slope>=0 && slope<=1) return 0;
    else if(slope>1) return 1;
    else if(slope<0 && slope>=-1) return 3;
    else return 2;
}

/**
 * @brief Draws a line between the given points by plotting each pixel on the line 
 * based on Bresenham's Line Drawing Algorithm
 * 
 * @param x1 The X coordinate of 1st point
 * @param y1 The Y coordinate of 1st point
 * @param x2 The X coordinate of 2nd point
 * @param y2 The Y coordinate of 2nd point
 */
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
    Helper::plotPoint(x+x1,y+y1);

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
                Helper::plotPoint(x1+x,y1+y);
                break;
            case 1:
                Helper::plotPoint(x1+y,y1+x);
                break;
            case 2:
                Helper::plotPoint(x1-y,y1+x);
                break;
            case 3:
                Helper::plotPoint(x1-x,y1+y);
                break;
        }
    }
    glEnd();
}

/**
 * @brief Draws a line between the given points with padding by plotting each pixel on the line 
 * based on Bresenham's Line Drawing Algorithm
 * 
 * @param x1 The X coordinate of 1st point
 * @param y1 The Y coordinate of 1st point
 * @param x2 The X coordinate of 2nd point
 * @param y2 The Y coordinate of 2nd point
 * @param padding The padding to be given from both the points i.e. it first clips the line from both ends
 * based on specified value
 */
void Line::drawLine(int x1, int y1, int x2, int y2, int padding){
    correctAlignment(&x1,&y1,&x2,&y2);
    double len = sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
    int x_correction = (int)((x2-x1)*padding/len);
    int y_correction = (int)((y2-y1)*padding/len);
    Line::drawLine(x1+x_correction, y1+y_correction, x2 - x_correction, y2-y_correction);
}

void render(void){
    Helper::clearScreen();
    Line line;
    line.drawLine(X1, Y1, X2, Y2);
    glFlush();
}

/**
 * @brief This function provides a validation check before 
 * plotting a point by determining if it is within screen bounds
 * 
 * @param x The x coordinate of the point to be checked
 * @param y The y coordinate of the point to be checked
 * @return true if the given point is inside the screen
 * @return false if the given point is outside the screen
 */
bool Line::insideScreen(int x,int y){
    bool status=true;
    if(x<0 || x> Helper::WINDOW_WIDTH)
        status=false;
    if(y<0 || y> Helper::WINDOW_HEIGHT)
        status=false;

    if(!status){
        std::cout<<"The points are not within the display area . Please enter again"<<std::endl;
    }
    return status;
}

/**
 * @brief 
 * This function is used to take coordinates as input from the user, 
 * and display a line between those coordinates on a window using OpenGL
 * @param argc Pointer to total number of arguments
 * @param argv The actual arguments to be passed to the function
 */
void Line::initLine(int *argc, char **argv){
    Line line;
    do{
        std::cout<<"enter x and y coordinates of the first point"<<std::endl;
        std::cin>>X1>>Y1;
    } while(!line.insideScreen(X1,Y1));

    do{
        std::cout<<"enter x and y coordinates of the second point"<<std::endl;
        std::cin>>X2>>Y2;
    } while(!line.insideScreen(X2,Y2));
    
    Helper::createWindow(argc, argv);
    glutDisplayFunc(render);
    glutMainLoop();
}
