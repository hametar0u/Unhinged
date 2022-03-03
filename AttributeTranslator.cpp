#include "AttributeTranslator.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

bool AttributeTranslator::Load(string filename) {
    ifstream file(filename);
    if (!file) return false;
    
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string source_attr;
        string source_val;
        string target_attr;
        string target_val;
        //getline succeeds if it gets at least one character (doesn't matter if there's no ,)
        if (!getline(iss, source_attr, ',')) return false; //invalid format
        if (!getline(iss, source_val, ',')) return false; //invalid format
        if (!getline(iss, target_attr, ',')) return false; //invalid format
        if (!getline(iss, target_val, ',')) return false; //invalid format
        
        cerr << source_attr << "," << source_val << "," << target_attr << "," << target_val << endl;
        
    }
    
    return true;
}
vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const {
    return {}; //TODO: implement
}
