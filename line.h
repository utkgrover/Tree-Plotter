#ifndef LINE_H
#define LINE_H

class Line{
    private:
    void correctAlignment(int*, int*, int*, int*);
    int getSlopeType(int, int, int, int);
    bool insideScreen(int, int);

    public:
    static void initLine(int *, char **);
    void drawLine(int, int, int, int);
    void drawLine(int, int, int, int, int);
};

#endif