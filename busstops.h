/*busstops.h*/

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

#include "busstop.h"
#include "dist.h"

using namespace std;

class BusStops{
private:
    vector<BusStop> MapBusStops;

public:
    BusStops(string filename);

    int getNumMapBusStops() const;

    static bool comp(BusStop& bs1, BusStop& bs2);

    void print();

    BusStop closestSouth(double lat, double lon);

    BusStop closestNorth(double lat, double lon);
};