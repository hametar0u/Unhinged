#ifndef AttributeTranslator_h
#define AttributeTranslator_h

#include <string>
#include <vector>
#include "provided.h"
#include "RadixTree.h"
using namespace std;

class AttributeTranslator {
public:
    AttributeTranslator() {} //TODO: ctor
    ~AttributeTranslator() {} //TODO: dtor
    
    bool Load(string filename);
    vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;

private:
    RadixTree<AttValPair> t;
};

#endif /* AttributeTranslator_hpp */
