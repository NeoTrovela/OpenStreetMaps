/*main.cpp*/

//
// Program to input Nodes (positions) and Buildings from
// an Open Street Map file.
// 


#include <iostream>
#include <string>

#include "curl_util.h"
#include "building.h"
#include "buildings.h"
#include "busstop.h"
#include "busstops.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"

#include "json.hpp"

using namespace std;
using namespace tinyxml2;
using json = nlohmann::json;


//
// main
//
int main()
{
  XMLDocument xmldoc;
  Nodes nodes;
  Buildings buildings;
  //BusStops busstops;

  CURL* curl = curl_easy_init();
  if(curl == nullptr){
    cout << "**ERROR:" << endl;
    cout << "**ERROR: unable to initialize curl library" << endl;
    cout << "**ERROR:" << endl;
    return 0;
  }
  
  cout << "** NU open street map **" << endl;

  string filename;

  cout << endl;
  cout << "Enter map filename> " << endl;
  getline(cin, filename);

  //
  // 1. load XML-based map file 
  //
  if (!osmLoadMapFile(filename, xmldoc))
  {
    // failed, error message already output
    return 0;
  }
  
  //
  // 2. read the nodes, which are the various known positions on the map:
  //
  nodes.readMapNodes(xmldoc);

  //
  // 3. read the university buildings:
  //
  buildings.readMapBuildings(xmldoc);

  //
  // read bus stops:
  //
  BusStops busstops("bus-stops.txt");

  //
  // 4. stats
  //
  cout << "# of nodes: " << nodes.getNumMapNodes() << endl;
  cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;
  cout << "# of bus stops: " << busstops.getNumMapBusStops() << endl;

  //
  // 5. now let the user for search for 1 or more buildings:
  //
  while (true)
  {
    string name;

    cout << endl;
    cout << "Enter building name (partial or complete), or * to list, or @ for bus stops, or $ to end> " << endl;

    getline(cin, name);

    if (name == "$") {
      break;
    }
    else if (name == "*") {
      buildings.print();
    }
    else if (name == "@"){
      busstops.print();
    }
    else {
      pair<double, double> loc;
      buildings.findAndPrint(name, nodes, busstops, curl);

      /*loc = buildings.getLocation(name, nodes);
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
      }*/
    }

  }//while

  //
  // done:
  //

  curl_easy_cleanup(curl);
  cout << endl;
  cout << "** Done **" << endl;
  /*cout << "# of calls to getID(): " << Node::getCallsToGetID() << endl;
  cout << "# of Nodes created: " << Node::getCreated() << endl;
  cout << "# of Nodes copied: " << Node::getCopied() << endl;*/
  cout << endl;

  return 0;
}
