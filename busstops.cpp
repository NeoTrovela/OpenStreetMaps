/*busstops.cpp*/

#include "busstops.h"

using namespace std;

bool BusStops::comp(BusStop& bs1, BusStop& bs2){
    return bs1.getStopID() < bs2.getStopID();
}

BusStops::BusStops(string filename){
    ifstream input;
    input.open(filename);

    if(!input.is_open()){ // file cannot be opened
        return;
    }

    while(!input.eof()){
        string line;
        getline(input, line);

        if(input.fail()){
            break;
        }

        stringstream parser(line);

        string stopID;
        string busRoute; 
        string stopName; 
        string direction; 
        string stopLocation; 
        string lat; 
        string lon;

        getline(parser, stopID, ',');
        getline(parser, busRoute, ',');
        getline(parser, stopName, ',');
        getline(parser, direction, ',');
        getline(parser, stopLocation, ',');
        getline(parser, lat, ',');
        getline(parser, lon, ',');

        BusStop s(stoi(stopID), stoi(busRoute), stopName, direction, stopLocation, stod(lat), stod(lon));

        this->MapBusStops.push_back(s);
    }
}

int BusStops::getNumMapBusStops() const{
    return (int) this->MapBusStops.size();
}

void BusStops::print(){
    sort(this->MapBusStops.begin(), this->MapBusStops.end(), BusStops::comp);
    for (BusStop S : this->MapBusStops) {
        S.print();
    }
}

BusStop BusStops::closestSouth(double lat, double lon){
    BusStop closestS = this->MapBusStops.front();
    double shortDistance = 1000000;
    //vector<double> allDistances;
    for (BusStop S : this->MapBusStops){
        if(S.getDirection() != "Southbound"){
            continue; // only want southbound bus stops
        }
        double busLat = S.getLat();
        double busLon = S.getLon();
        double distance = distBetween2Points(lat, lon, busLat, busLon);
        //allDistances.push_back(distance);
        //sort(allDistances.begin(), allDistances.end());
        if(distance < shortDistance){
            closestS = S;
            shortDistance = distance;
        } // new short distance and busstop
    }
    cout << "Closest southbound bus stop: " << endl;
    closestS.printDistance(shortDistance);

    return closestS;
}

BusStop BusStops::closestNorth(double lat, double lon){
    BusStop closestN = this->MapBusStops.front();
    double shortDistance = 1000000;
    for (BusStop N : this->MapBusStops){
        if(N.getDirection() != "Northbound"){
            continue;
        }
        double busLat = N.getLat();
        double busLon = N.getLon();
        double distance = distBetween2Points(lat, lon, busLat, busLon);
        //allDistances.push_back(distance);
        //sort(allDistances.begin(), allDistances.end());
        if(distance < shortDistance){
            closestN = N;
            shortDistance = distance;
        }
    }
    cout << "Closest northbound bus stop: " << endl;
    closestN.printDistance(shortDistance);

    return closestN;
}