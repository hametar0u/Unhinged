#ifndef AttributeTranslator_h
#define AttributeTranslator_h

#include <string>
#include <vector>
#include <unordered_set>
#include "provided.h"
#include "RadixTree.h"
using namespace std;

class AttributeTranslator {
public:
    AttributeTranslator() {} //TODO: ctor
    ~AttributeTranslator() {} //TODO: dtor
    
    bool Load(string filename);
    vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) ; //TODO: add const

private:
    RadixTree<unordered_set<string>> t; //TODO: change back to attvalpair
};

#endif /* AttributeTranslator_hpp */
