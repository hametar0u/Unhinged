//
//  PersonProfile.cpp
//  Unhinged
//
//  Created by Big Sad on 2022-03-02.
//

#include "PersonProfile.h"

void PersonProfile::AddAttValPair(const AttValPair& attval) {
    //break up attval into attribute -> set of vals
    
    unordered_set<string>* attr = t.search(attval.attribute);
    if (attr != nullptr) { //if attr already in tree,
        attr->insert(attval.value);
    }
    else {
        unordered_set<string> vals;
        vals.insert(attval.value);
        t.insert(attval.attribute, vals);
    }
    
    v.push_back(attval);
    m_numPairs++;
}

int PersonProfile::GetNumAttValPairs() const {
    return m_numPairs;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const {
    if (attribute_num >= v.size()) return false;
    attval = v.at(attribute_num);
    return true;
}
