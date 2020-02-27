#include<iostream>
#include"line.h"
#include"circle.h"

int main(int argc, char **argv){
    std::cout<<"Computer Graphics Assignment 1 "<<std::endl;
    std::cout<<"Team members- "<<std::endl;
    std::cout<<"Utkarsh Grover , 2017A7PS1428H "<<std::endl;
    std::cout<<"Prateek Agarwal , 2017A7PS0075H"<<std::endl;
    std::cout<<std::endl<<std::endl;

    std::cout<<"choose option to continue"<<std::endl;
    std::cout<<"to draw a Line press 1 "<<std::endl;
    std::cout<<"to draw a Circle press 2 "<<std::endl;
    std::cout<<"to draw a Tidier-Graph press 3 "<<std::endl;
    std::cout<<"to exit press 9 "<<std::endl;

    int user_input;
    std::cin>>user_input;

    switch(user_input){
        case 1:
            //code for line
            Line::initLine(&argc, argv);
        case 2:
            //code for circle
            Circle::initCircle(&argc, argv);
        case 3 :
            //code for graph
        case 9:
            exit(0);
        default:
            std::cout<<"Input doesn't match any input , please enter again"<<std::endl;
    }
}