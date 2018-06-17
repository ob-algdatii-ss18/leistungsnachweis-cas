//
// Created by chris on 27.04.18.
//
#include "prims/Prims.h"
#include "recursiveDivision/RecursiveDivision.h"
#include "recursiveBacktracker/RecursiveBacktracker.h"

using namespace std;
int main(int argc, const char *argv[]){

    helloFromPrims();

    RecursiveDivision rb;
    int answer = rb.generateMaze();
    if (answer != 0)
    {
        exit(1);
    }

    RecursiveBacktracker rb;
    int result = rb.startMaze();
    if(result != 0)
    {
        exit(1);
    }

    helloFromRecDiv();

    return 0;
}
