/*building.cpp*/

//
// A building in the Open Street Map.
// 


#include <iostream>

#include "building.h"

using namespace std;


//
// constructor
//
Building::Building(long long id, string name, string streetAddr)
  : ID(id), Name(name), StreetAddress(streetAddr)
{
  //
  // the proper technique is to use member initialization list above,
  // in the same order as the data members are declared:
  //
  //this->ID = id;
  //this->Name = name;
  //this->StreetAddress = streetAddr;

  // vector is default initialized by its constructor
}

//
// containsThisNode
//
// Returns true if the building's nodes contains the given node id,
// false if not.
//
bool Building::containsThisNode(long long nodeid)
{
  for (long long id : this->NodeIDs)
  {
    if (nodeid == id)
      return true;
  }

  // 
  // if get here, not found:
  //
  return false;
}

//
// print
// 
// prints information about a building --- id, name, etc. -- to
// the console. The function is passed the Nodes for searching 
// purposes.
//
void Building::print(Nodes& nodes)
{
  cout << this->Name << endl;
  cout << "Address: " << this->StreetAddress << endl;
  cout << "Building ID: " << this->ID << endl;

  // cout << "Nodes:" << endl;
  cout << "# perimeter nodes: ";
  int pNodes = 0;
  for (long long nodeid : this->NodeIDs)
  {
    pNodes++;
    /*cout << "  " << nodeid << ": ";

    double lat = 0.0;
    double lon = 0.0;
    bool entrance = false;

    bool found = nodes.find(nodeid, lat, lon, entrance);

    if (found) {
      cout << "(" << lat << ", " << lon << ")";

      if (entrance)
        cout << ", is entrance";

      cout << endl;
    }
    else {
      cout << "**NOT FOUND**" << endl;
    }*/
  }//for
  cout << pNodes << endl;
}

//
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}

pair<double, double> Building::getLocation(const Nodes& nodes){
  // loop through nodes
  // get average lat and lon
  // return pair of them
  double totalLat = 0;
  double totalLon = 0;
  double numNode = 0;
  
  for(long long nodeid : this->NodeIDs){
    double lat = 0.0;
    double lon = 0.0;
    bool entrance = false;

    bool found = nodes.find(nodeid, lat, lon, entrance);

    if(found){
      numNode++;
      totalLat += lat;
      totalLon += lon;
    }
  }
  double avgLat = totalLat/numNode;
  double avgLon = totalLon/numNode;

  return make_pair(avgLat, avgLon);
}
