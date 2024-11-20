/*buildings.cpp*/

//
// A collection of buildings in the Open Street Map.
// 


#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include "curl_util.h"
#include "buildings.h"
#include "nodes.h"
#include "busstops.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;


//
// readMapBuildings
//
// Given an XML document, reads through the document and 
// stores all the buildings into the given vector.
//
void Buildings::readMapBuildings(XMLDocument& xmldoc)
{
  XMLElement* osm = xmldoc.FirstChildElement("osm");
  assert(osm != nullptr);

  //
  // Parse the XML document way by way, looking for university buildings:
  //
  XMLElement* way = osm->FirstChildElement("way");

  while (way != nullptr)
  {
    const XMLAttribute* attr = way->FindAttribute("id");
    assert(attr != nullptr);

    //
    // if this is a building, store info into vector:
    //
    if (osmContainsKeyValue(way, "building", "university"))
    {
      string name = osmGetKeyValue(way, "name");

      string streetAddr = osmGetKeyValue(way, "addr:housenumber")
        + " "
        + osmGetKeyValue(way, "addr:street");

      //
      // create building object, then add the associated
      // node ids to the object:
      //
      long long id = attr->Int64Value();

      Building B(id, name, streetAddr);

      XMLElement* nd = way->FirstChildElement("nd");

      while (nd != nullptr)
      {
        const XMLAttribute* ndref = nd->FindAttribute("ref");
        assert(ndref != nullptr);

        long long id = ndref->Int64Value();

        B.add(id);

        // advance to next node ref:
        nd = nd->NextSiblingElement("nd");
      }

      //
      // add the building to the vector:
      //
      this->MapBuildings.push_back(B);
    }//if

    way = way->NextSiblingElement("way");
  }//while

  //
  // done:
  //
}

//
// print
//
// prints each building (id, name, address) to the console.
//
void Buildings::print()
{
  for (const Building& B : this->MapBuildings) {
    cout << B.ID << ": " << B.Name << ", " << B.StreetAddress << endl;
  }
}

//
// findAndPrint
//
// Prints each building that contains the given name.
//
void Buildings::findAndPrint(string name, Nodes& nodes, BusStops& busstops, CURL* curl)
{
  // 
  // find every building that contains this name:
  //
  for (Building& B : this->MapBuildings)
  {
    if (B.Name.find(name) != string::npos) { // contains name:
      B.print(nodes);
      pair<double, double> loc = B.getLocation(nodes);
      cout << "Location: (" << loc.first << ", " << loc.second << ")" << endl;
      // closest bus stops given location
      if(loc.first == 0 && loc.second == 0){ // building doesnt exist
        continue;
      }

      BusStop closestS = busstops.closestSouth(loc.first, loc.second);
 
      string southUrl = closestS.getUrl();
      string responseS;
      // south predictions
      if(!callWebServer(curl, southUrl, responseS)){ // could not open url
        cout << "  <<bus predictions unavailable, call failed>>" << endl;
      }
      else{
        closestS.printBusPredictions(responseS);
      }

      BusStop closestN = busstops.closestNorth(loc.first, loc.second);

      string northUrl = closestN.getUrl();
      string responseN;
      // north predictions
      if(!callWebServer(curl, northUrl, responseN)){ // could not open url
        cout << "  <<bus predictions unavailable, call failed>>" << endl;
      }
      else{
        closestN.printBusPredictions(responseN);
      }
    }
  }
}

//
// accessors / getters
//
int Buildings::getNumMapBuildings() {
  return (int) this->MapBuildings.size();
}

pair<double, double> Buildings::getLocation(string name, Nodes& nodes){
  for (Building& B : this->MapBuildings)
  {
    if (B.Name.find(name) != string::npos) { // contains name:
      pair<double, double> location = B.getLocation(nodes);
      // closest bus stops given location
      return location;
    }
  }
  return make_pair(0,0);
}