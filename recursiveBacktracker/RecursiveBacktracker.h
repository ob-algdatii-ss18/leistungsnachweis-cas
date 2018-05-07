//
// Created by chris on 27.04.18.
//

#ifndef LEISTUNGSNACHWEIS_CAS_RECURSIVEBACKTRACKER_H
#define LEISTUNGSNACHWEIS_CAS_RECURSIVEBACKTRACKER_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <vector>

using namespace std;

typedef struct
{
    bool up;
    bool down;
    bool left;
    bool right;
    int x, y; //Cell position - little waste of memory, but it allows faster generation
    void *parentCell; //Pointer to parent cell
    char image; //Character to be displayed
    char dirs; //Directions that still haven't been explored

}Cell;

class RecursiveBacktracker {

private:
    vector<Cell *> newcells;
    Cell *dummy; //Cells array
    int width, height; //Maze dimension
    char wall = '#';
    char path = '.';

public:

    int initMaze( );
    Cell *backtracking( Cell *c );
    void drawMaze( );
    int startMaze( );


    double testMethod();
};


#endif //LEISTUNGSNACHWEIS_CAS_RECURSIVEBACKTRACKER_H
