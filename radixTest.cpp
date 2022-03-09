//#include "RealRadixTree.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//int main() {
//    RadixTree<int> t;
//    t.insert("", 1);
//    assert( t.search("") == nullptr);
//    
//    t.insert("cat", 1); //test no_common_substr
//    t.insert("dog", 2);
//    assert( t.search("cat") && t.search("dog") );
//    
//    t.insert("cater", 3); //test trailing_key
//    assert( t.search("cat") && t.search("cater") && *t.search("cat") == 1 && *t.search("cater") == 3 );
//    
//    t.insert("c", 4); //test trailing_label
//    assert( t.search("c") && *t.search("c") == 4 && t.search("cat") && *t.search("cat") == 1 );
//    
//    t.insert("campfire", 5); //test mid split
//    assert( t.search("cat") && t.search("campfire") && *t.search("cat") == 1 && *t.search("campfire") == 5 );
//    
//    t.insert("camping", 6); //if key < label size
//    assert( t.search("camping") && t.search("campfire") && *t.search("camping") == 6 && *t.search("campfire") == 5 );
//    
//    //add more stuff to be sure
//    t.insert("crown", 6); //if key < label size
//    assert( t.search("crown") && t.search("campfire") && *t.search("crown") == 6 && *t.search("campfire") == 5 );
//    t.insert("ditch", 6); //if key < label size
//    assert( t.search("ditch") && t.search("campfire") && *t.search("ditch") == 6 && *t.search("campfire") == 5 );
//    t.insert("quote", 6); //if key < label size
//    assert( t.search("quote") && t.search("ditch") && *t.search("quote") == 6 && *t.search("ditch") == 6 );
//    t.insert("opinion", 6); //if key < label size
//    assert( t.search("opinion") && t.search("campfire") && *t.search("opinion") == 6 && *t.search("campfire") == 5 );
//    t.insert("overall", 6); //if key < label size
//    assert( t.search("overall") && t.search("campfire") && *t.search("overall") == 6 && *t.search("campfire") == 5 );
//    t.insert("yearn", 6); //if key < label size
//    assert( t.search("yearn") && t.search("campfire") && *t.search("yearn") == 6 && *t.search("campfire") == 5 );
//    
//    t.insert("hobby,poetry", 7);
//    t.insert("hobby,debate", 8);
//    
//    int* emailsWithAttval = t.search("hobby,poetry");
//    if (emailsWithAttval == nullptr) {
//        int e = 9;
//        t.insert("hobby,poetry", e);
//    }
////    t.insert("hobby,poetry", 9);
//    
//    assert( *t.search("hobby,poetry") == 7 );
//    
//    cout << "all tests passed" << endl;
//}
