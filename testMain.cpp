//
// Created by chris on 27.04.18.
//
#include "prims/Prims.h"
#include "recursiveDivision/RecursiveDivision.h"


using namespace std;
int main(int argc, const char *argv[]){

    helloFromPrims();

    RecursiveDivision rb;
    int answer = rb.generateMaze();
    if (answer != 0)
    {
        exit(1);
    }

    helloFromRecDiv();

    return 0;
}
