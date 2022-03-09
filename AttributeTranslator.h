#ifndef AttributeTranslator_h
#define AttributeTranslator_h

#include <string>
#include <vector>
#include <unordered_set>
#include "provided.h"
#include "RadixTree.h"
#include "utility.h"
using namespace std;

class AttributeTranslator {
public:
    AttributeTranslator() {}
    ~AttributeTranslator() {}
    
    bool Load(string filename);
    vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;

private:
    struct pair {
        pair() {}
        pair(AttValPair attval) {
            s.insert(attVal2Str(attval.attribute, attval.value));
            v.push_back(attval);
        }
        
        unordered_set<string> s;
        vector<AttValPair> v;
    };
    
    RadixTree<pair> t;
};

#endif /* AttributeTranslator_hpp */
