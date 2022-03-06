//
//  PersonProfile.cpp
//  Unhinged
//
//  Created by Big Sad on 2022-03-02.
//

#include "PersonProfile.h"
#include "utility.h"

void PersonProfile::AddAttValPair(const AttValPair& attval) {
    //break up attval into attribute -> set of vals
    string pair = attVal2Str(attval.attribute, attval.value);
    if (s.insert(pair).second) {
        t.insert(attval.attribute, attval.value); //tree doesn't do shit so whatever
        v.push_back(attval);
    }
    
    
    
    
    
//    unordered_set<string>* attr = t.search(attval.attribute);
//    if (attr != nullptr) { //if attr already in tree,
//        attr->insert(attval.value);
//    }
//    else {
//        unordered_set<string> vals;
//        vals.insert(attval.value);
//        t.insert(attval.attribute, vals);
//    }
//
//    v.push_back(attval);
//    m_numPairs++;
}

int PersonProfile::GetNumAttValPairs() const {
    return v.size();
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const {
    if (attribute_num >= v.size()) return false;
    attval = v.at(attribute_num);
    return true;
}
