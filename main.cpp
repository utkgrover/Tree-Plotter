#include<iostream>
#include"line.h"
#include"circle.h"
#include"tree.h"

int main(int argc, char **argv){
    std::cout<<"Computer Graphics Assignment 1 "<<std::endl;
    std::cout<<"Team members - "<<std::endl;
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
            Line::initLine(&argc, argv);
            break;
        case 2:
            Circle::initCircle(&argc, argv);
            break;
        case 3 :
            Tree::initTree(&argc, argv);
            break;
        case 9:
            exit(0);
        default:
            std::cout<<"Invalid Input"<<std::endl;
    }
}