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
        string src = source_attr + "," + source_val;
        string vals = target_attr + "," + target_val; //TODO: use target instead in prod
        
        unordered_set<string>* targets = t.search(src);
        if (targets != nullptr) {
            targets->insert(target.attribute + "," + target.value);
        }
        else {
            unordered_set<string> targetPairs;
            targetPairs.insert(vals);
            t.insert(src, targetPairs);
        }
        
    }
    
    return true;
}

vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) { //TODO: add const
    
    //note: by using an unordered set instead of a vector in the tree, this operation because O(N) instead of O(1)
    
    vector<AttValPair> compatibles;
//    AttValPair src(source.attribute, source.value);
    string src = source.attribute + "," + source.value;
    
    
    unordered_set<string>* targets = t.search(src);
    if (targets == nullptr) return {};
    
    for (auto pair : *targets) {
        string target_attr = pair.substr(0, pair.find(','));
        string target_val = pair.substr(pair.find(',') + 1);
        AttValPair target_pair(target_attr, target_val);
        
        compatibles.push_back(target_pair);
    }
    
    for (auto pair : compatibles) {
        cerr << pair.attribute << "," << pair.value << endl;
    }
    
    return compatibles;
}
