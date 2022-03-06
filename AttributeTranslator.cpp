#include "AttributeTranslator.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "utility.h"
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
        string src = attVal2Str(source_attr, source_val);
        string targetStr = attVal2Str(target_attr, target_val); //TODO: use target instead in prod or not lol
        
        pair* targets = t.search(src);
        if (!targets) {
            pair p(target);
            t.insert(src, p);
        }
        else {
            if (targets->s.insert(targetStr).second) {
                targets->v.push_back(target);
            }
        }
    }
    
    return true;
}

vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) { //TODO: add const
    string src = attVal2Str(source.attribute, source.value);
    
    
    pair* targets = t.search(src);
    if (targets == nullptr) return {};
    return targets->v;
}
