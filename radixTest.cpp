#include "RealRadixTree.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
    RadixTree<int> t;
    t.insert("", 1);
    assert( t.search("") == nullptr);
    
    t.insert("cat", 1); //test no_common_substr
    t.insert("dog", 2);
    assert( t.search("cat") && t.search("dog") );
    
    t.insert("cater", 3); //test trailing_key
    assert( t.search("cat") && t.search("cater") && *t.search("cat") == 1 && *t.search("cater") == 3 );
    
    t.insert("c", 4); //test trailing_label
    assert( t.search("c") && *t.search("c") == 4 && t.search("cat") && *t.search("cat") == 1 );
    
    cout << "all tests passed" << endl;
}
