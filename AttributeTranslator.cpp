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
        string source_attr; string source_val;
        string target_attr; string target_val;
        //getline succeeds if it gets at least one character (doesn't matter if there's no ,)
        if (!getline(iss, source_attr, ',')) return false; //invalid format
        if (!getline(iss, source_val, ',')) return false; //invalid format
        if (!getline(iss, target_attr, ',')) return false; //invalid format
        if (!getline(iss, target_val, ',')) return false; //invalid format
        
        AttValPair target(target_attr, target_val);
        t.insert(source_attr + "," + source_val, target);
    }
    
    return true;
}

vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) { //TODO: add const
    vector<AttValPair> compatibles;
    AttValPair src(source.attribute, source.value);
    AttValPair* i = t.search(src.attribute + "," + src.value);
    compatibles.push_back(*i);
    for (auto pair : compatibles) {
        cerr << pair.attribute << "," << pair.value << endl;
    }
    
    return compatibles;
}
