#ifndef CIRCLE_H
#define CIRCLE_H

class Circle{
    private:
    void getAllPoints(int, int, int, int);

    public:
    static void initCircle(int* , char**);
    void drawCircle(int, int, int);
};

#endif