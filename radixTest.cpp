#include "RealRadixTree.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
    RadixTree<int> t;
    t.insert("", 1);
    assert( t.search("") == nullptr);
    
    cout << "all tests passed" << endl;
}
