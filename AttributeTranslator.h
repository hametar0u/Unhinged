#ifndef AttributeTranslator_h
#define AttributeTranslator_h

#include <string>
#include <vector>
#include "provided.h"
using namespace std;

class AttributeTranslator {
public:
    AttributeTranslator() {} //TODO: ctor
    ~AttributeTranslator() {} //TODO: dtor
    
    bool Load(string filename);
    vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
    
    
};

#endif /* AttributeTranslator_hpp */
