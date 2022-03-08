//
//  utility.cpp
//  Unhinged
//
//  Created by Big Sad on 2022-03-06.
//

#include "utility.h"

string attVal2Str(string attr, string val) {
    return attr + ',' + val;
}

AttValPair str2AttVal(string attval) {
    AttValPair a;
    a.attribute = attval.substr(0, attval.find(','));
    a.value = attval.substr(attval.find(',')+1);
    return a;
}

//bool operator< (const AttValPair& a, const AttValPair& b) {
//    
//}
