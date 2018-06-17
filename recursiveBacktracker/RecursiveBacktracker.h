/**
* Created by Anja Wimmer on 27.04.18.
*/

#ifndef LEISTUNGSNACHWEIS_CAS_RECURSIVEBACKTRACKER_H
#define LEISTUNGSNACHWEIS_CAS_RECURSIVEBACKTRACKER_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <vector>
#include <bitset>

using namespace std;

typedef struct
{
    char directions;
    //bool directions[4]; //up, down, left, right
    int x, y; //Cell position - little waste of memory, but it allows faster generation
    void *parentCell; //Pointer to parent cell
    char image; //Character to be displayed

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
