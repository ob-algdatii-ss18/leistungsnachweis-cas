//
// Created by chris on 27.04.18.
//
#include "prims/Prims.h"
#include "LabGraph.h"
#include "recursiveDivision/RecursiveDivision.h"


using namespace std;
int main(int argc, const char *argv[]){

    helloFromPrims();

    auto t = new LabGraph(20,20);//breit,höhe
    t->easyTest();

    /*
    RecursiveDivision rb;
    int answer = rb.generateMaze();
    if (answer != 0)
    {
        exit(1);
    }

    helloFromRecDiv();
*/
    return 0;
}
