/*footways.cpp*/

#include <iostream>
#include <vector>
#include <cassert>

#include "footways.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

void Footways::readMapFootways(XMLDocument& xmldoc){
    XMLElement* osm = xmldoc.FirstChildElement("osm");
    XMLElement* way = osm->FirstChildElement("way"); // start of traversal

    while(way != nullptr){
        if (osmContainsKeyValue(way, "highway", "footway") || osmContainsKeyValue(way, "area:highway", "footway")){
            const XMLAttribute* idref = way->FindAttribute("id"); // grabbing id value
            long long id = idref->Int64Value();

            Footway F(id);

            XMLElement* nd = way->FirstChildElement("nd");
            while(nd != nullptr){
                const XMLAttribute* ndref = nd->FindAttribute("ref");
                assert(ndref != nullptr);

                long long nextid = ndref->Int64Value();

                F.add(nextid);
                nd = nd->NextSiblingElement("nd");
            }

            MapFootways.push_back(F);
        }
        way = way->NextSiblingElement("way");
    }
}

int Footways::getNumMapFootways() const{
    return MapFootways.size();
}

void Footways::isIntersection(vector<long long> B_nodeIDs){
    vector<long long> intersections; // vector of node ids to loop once finished

    for(Footway way : MapFootways){
        if(way.intersect_exist(B_nodeIDs)){
            intersections.emplace_back(way.ID);
        }
    }

    // sort(intersections.begin(), intersections.end());
    // dont have to sort if footways is already sorted

    if(intersections.size() == 0){
        cout << " None " << endl;
    }
    else{
        for(long long i : intersections){
            cout << " Footway " << i << endl;
        }
    }    
}