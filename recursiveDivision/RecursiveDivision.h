//
// Created by chris on 27.04.18.
//

#ifndef LEISTUNGSNACHWEIS_CAS_RECURSIVEDIVISION_H
#define LEISTUNGSNACHWEIS_CAS_RECURSIVEDIVISION_H

#include <iostream>

void helloFromRecDiv();

class RecursiveDivision {
public:
    enum Orientation {HORIZONTAL, VERTICAL};

    int testMethod();
    RecursiveDivision::Orientation chooseOrientation(int width, int height);
};


#endif //LEISTUNGSNACHWEIS_CAS_RECURSIVEDIVISION_H
