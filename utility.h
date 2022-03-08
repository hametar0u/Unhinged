//
//  utility.hpp
//  Unhinged
//
//  Created by Big Sad on 2022-03-06.
//

#ifndef utility_hpp
#define utility_hpp

#include <string>
#include "provided.h"
using namespace std;

string attVal2Str(string attr, string val);
AttValPair str2AttVal(string attval);

//bool operator< (const AttValPair& a, const AttValPair& b); //TODO: remove if not used

#endif /* utility_hpp */
