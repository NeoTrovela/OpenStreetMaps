/*bus stop.h*/

#pragma once

#include <string>
#include <iostream>

using namespace std;

class BusStop{
private:
    int StopID;
    int BusRoute;
    string StopName;
    string Direction;
    string StopLocation;
    double Lat;
    double Lon;

public:
    //
    // constructor
    //
    BusStop(int stopID, int busRoute, string stopName, string direction, string stopLocation, double lat, double lon);

    //
    // copy constructor:
    //
    //BusStop(const BusStop& other);

    void print();

    void printDistance(double distance);

    double getLat();

    double getLon();

    int getStopID();

    string getDirection();

    string getUrl();

    void printBusPredictions(string response);
};