/*footway.cpp*/

#include "footway.h"
#include <algorithm>

using namespace std;

//
// Constructor
//
Footway::Footway(long long id)
    : ID(id)
{}

// 
// Helpers
//
void Footway::add(long long nodeid){
    this->NodeIDs.push_back(nodeid);
}

bool Footway::intersect_exist(vector<long long> B_Node){ 
    // grab the buildings node ids
    // check if footway node is in the B vector using find (does this count as a loop?)

    for(long long i : this->NodeIDs){
        if (find(B_Node.begin(), B_Node.end(), i) != B_Node.end()){
            return true; // meant for helper function 
        }
    }
    return false;
}