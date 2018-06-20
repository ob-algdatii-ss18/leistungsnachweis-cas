//
// Created by chris on 27.04.18.
//

#include "LabGraph.h"
#include "recursiveDivision/RecursiveDivision.h"
#include "recursiveBacktracker/RecursiveBacktracker.h"

using namespace std;
int main(int argc, const char *argv[]){

    //helloFromPrims();

    string input;
    cout << "Choose your algorithm \n 1: Prim \n 2: RecursiveDivision \n 3: RecursiveBacktracker" ;
    getline (cin, input);
    int alg = stoi(input);

    if(alg == 1) {
        auto t = new LabGraph(20, 20);//breit,höhe
        t->easyTest();
    }

    if(alg == 2) {
        RecursiveDivision rb;
        int answer = rb.generateMaze(std::cin);
        if (answer != 0) {
            exit(1);
        }
    }
    if(alg == 3) {
        RecursiveBacktracker rb;
        int result = rb.startMaze();
        if (result != 0) {
            exit(1);
        }
    }
    //helloFromRecDiv();

    return 0;
}
