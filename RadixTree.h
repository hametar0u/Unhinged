#ifndef RadixTree_h
#define RadixTree_h

#include <string>
#include <unordered_map> //TODO: remove in prod
#include <vector>
#include <iostream> //TODO: remove in prod
#include <typeinfo>
using namespace std;

//TODO: replace with actual radix tree implementation
template <typename ValueType>
class RadixTree {
public:
    RadixTree() {} //TODO: ctor
    ~RadixTree() {} //TODO: dtor
    void insert(string key, const ValueType& value) {
        ValueType val = value;
        tree[key] = val;
    }
    
    ValueType* search(string key) const {
        if (tree.find(key) == tree.end()) return nullptr;
        return &tree.at(key);
    }
private:
    unordered_map<string, ValueType> tree;
    vector<ValueType> v;
};

#endif /* RadixTree_h */
