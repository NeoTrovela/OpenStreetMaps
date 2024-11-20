/*footways.h*/

#pragma once

#include <vector>
#include <iostream>

#include "footway.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Footways{
public:
    vector<Footway> MapFootways;

    //
    // readMapFootways
    //
    // reads given XMLDoc
    void readMapFootways(XMLDocument& xmldoc);

    //
    // Accessors
    //
    int getNumMapFootways() const;

    //
    // Helpers
    //
    void isIntersection(vector<long long> B_nodeIDs);
};