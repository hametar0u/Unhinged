//
//  PersonProfile.cpp
//  Unhinged
//
//  Created by Big Sad on 2022-03-02.
//

#include "PersonProfile.h"

void PersonProfile::AddAttValPair(const AttValPair& attval) {
    t.insert(attval.attribute, attval);//TODO: sussy af
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
