#ifndef RadixTree_h
#define RadixTree_h

#include <string>
using namespace std;

template <typename ValueType>
class RadixTree {
public:
    RadixTree() {} //TODO: ctor
    ~RadixTree() {} //TODO: dtor
    void insert(string key, const ValueType& value);
    ValueType* search(string key) const;
};

#endif /* RadixTree_h */
