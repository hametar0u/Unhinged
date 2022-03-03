#include "AttributeTranslator.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

bool AttributeTranslator::Load(string filename) {
    ifstream file(filename);
    if (!file) return false;
    
    while (!file.eof()) {
        string line;
        getline(file, line);
        //dude idk wtf
    }
    
    return true;
}
vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const {
    return {}; //TODO: implement
}
