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
    RadixTree() : m_size(0) {}
    ~RadixTree() {
//        for (auto node : tree) {
//            delete node;
//        }
    } //TODO: dtor
    void insert(string key, const ValueType& value) {
        tree[key] = value;
        m_size = tree.size(); //TODO: for testing only
    }
    
    ValueType* search(string key) { //TODO: add const back in later
        auto entry = tree.find(key);
        if (entry == tree.end()) return nullptr;
        return &tree.at(key);
    }
private:
    unordered_map<string, ValueType> tree;
    int m_size;
};

#endif /* RadixTree_h */
