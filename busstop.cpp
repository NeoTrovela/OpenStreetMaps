/*busstop.cpp*/

#include <stdexcept>

#include "busstop.h"
#include "curl_util.h"

#include "json.hpp"

using namespace std;
using json = nlohmann::json;

//
// constructor
//
BusStop::BusStop(int stopID, int busRoute, string stopName, string direction, string stopLocation, double lat, double lon)
    : StopID(stopID), BusRoute(busRoute), StopName(stopName), Direction(direction), StopLocation(stopLocation), Lat(lat), Lon(lon)
{}

void BusStop::print(){
    cout << this->StopID << ": bus " << this->BusRoute << ", " << this->StopName << ", " << this->Direction << ", " << this->StopLocation << ", location (" << this->Lat << ", " << this->Lon << ") " << endl;
}

void BusStop::printDistance(double distance){
    cout << "  " << this->StopID << ": " << this->StopName << ", bus #"  << this->BusRoute << ", " << this->StopLocation << ", " << distance << " miles " << endl;
}

int BusStop::getStopID(){
    return this->StopID;
}

double BusStop::getLat(){
    return this->Lat;
}

double BusStop::getLon(){
    return this->Lon;
}

string BusStop::getDirection(){
    return this->Direction;
}

string BusStop::getUrl(){
    string busNum = to_string(this->BusRoute);
    string busID = to_string(this->StopID);
    string url = "http://localhost:8080/bustime/api/v2/getpredictions?key=cQ2snAkM49vrZ2494zJ5fV6Ci&rt="+busNum+"&stpid="+busID+"&format=json";
    return url;
}

void BusStop::printBusPredictions(string response){
    // get string url then call callWebServer function and see if it returns false
    // if return false use busstops.printUnavailable
    // if return true, use busstops.printBusPredictions
    auto jsondata = json::parse(response);
    auto predictions = jsondata["bustime-response"];

    /*if(predictions.size() == 0){
        cout << "  <<no predictions available>>" << endl;
        return;
    }*/
    int i = 0;
    
    for(auto& M : predictions["prd"]){
        try{
            i++;
            cout << "  vehicle #" << stoi(M["vid"].get_ref<std::string&>()) << " on route " << stoi(M["rt"].get_ref<std::string&>()) << " travelling " << M["rtdir"].get_ref<std::string&>() << " to arrive in " << stoi(M["prdctdn"].get_ref<std::string&>()) << " mins" << endl;
        }
        catch (exception& e) {
            cout << "  error" << endl;
            cout << "  malformed CTA response, prediction unavailable"
                << " (error: " << e.what() << ")" << endl;
        }
        
    }
    if(i == 0){
        cout << "  <<no predictions available>>" << endl;
    }

}