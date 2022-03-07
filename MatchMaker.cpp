#include "MatchMaker.h"
#include "utility.h"
#include <algorithm>
#include <iostream>
using namespace std;

vector<EmailCount> MatchMaker::IdentifyRankedMatches(string email, int threshold) /*const*/ {
    
    unordered_set<string> compatibleAttrSet;
    unordered_map<string, int> emailCounts;
    vector<EmailCount> matches;
//    vector<AttValPair> compatibleAttr;
    
    PersonProfile* member = m_mdb.GetMemberByEmail(email);
    if (!member) return {};
    
    for (int i = 0; i < member->GetNumAttValPairs(); i++) {
        AttValPair member_attr;
        member->GetAttVal(i, member_attr);
//        appendVector(compatibleAttr, m_at.FindCompatibleAttValPairs(member_attr));
        
        vector<AttValPair> compatibleAttr = m_at.FindCompatibleAttValPairs(member_attr);
        for (auto attr : compatibleAttr) {
            compatibleAttrSet.insert(attVal2Str(attr.attribute, attr.value));
        }
        
    }
    for (auto attr : compatibleAttrSet) {
        cerr << "compatible trait: " << attr << endl; //TODO: remove in prod
        AttValPair attval = str2AttVal(attr);
        vector<string> matchingMembers = m_mdb.FindMatchingMembers(attval);
        for (auto matchingMember : matchingMembers) {
            if (emailCounts.find(matchingMember) == emailCounts.end()) {
                emailCounts[matchingMember] = 1;
            }
            else {
                emailCounts[matchingMember]++;
            }
        }
        
    }
    
    for (auto candidate : emailCounts) {
        if (candidate.second >= threshold) {
            EmailCount e(candidate.first, candidate.second);
            matches.push_back(e);
        }
    }
    
    //since I have O(n^2) somewhere doesn't matter if I nlogn sort
//    sort(matches.begin(), matches.end(), emailSortOrder);
    
    return matches;
}
