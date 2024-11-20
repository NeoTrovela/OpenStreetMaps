/*footway.h*/

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "node.h"
#include "nodes.h"

using namespace std;

// Footway
// ID (long long)
// vector<long long> NodeIDs
// footways are ways in the osm file
// has key value pair of ("highway", "footway") or ("addr:highway", "footway")

class Footway{
public:
    long long ID;
    vector<long long> NodeIDs;

    //
    // Constructor
    //
    Footway(long long id);

    //
    // Helpers
    //
    void add(long long nodeid);
    bool intersect_exist(vector<long long> B_Node); 
    
};
