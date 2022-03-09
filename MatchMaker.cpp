#include "MatchMaker.h"
#include "utility.h"
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

//helper function (comparison operator for emailcount)
bool operator< (const EmailCount& a, const EmailCount& b) {
    if (a.count == b.count)
        return a.email < b.email;
    return a.count > b.count;
}


vector<EmailCount> MatchMaker::IdentifyRankedMatches(string email, int threshold) const {
    
    unordered_set<string> compatibleAttrSet; //remove duplicate attvals
    unordered_map<string, int> emailCounts; //makes it easy to increment counts
//    set<EmailCount> emailCounts;
    vector<EmailCount> matches;
//    vector<AttValPair> compatibleAttr;
    
    const PersonProfile* member = m_mdb.GetMemberByEmail(email);
    if (!member) return {};
    
    for (int i = 0; i < member->GetNumAttValPairs(); i++) {
        AttValPair member_attr;
        member->GetAttVal(i, member_attr);
        
        vector<AttValPair> compatibleAttr = m_at.FindCompatibleAttValPairs(member_attr);
        for (auto attr : compatibleAttr) {
            compatibleAttrSet.insert(attVal2Str(attr.attribute, attr.value));
        }
        
    }
    for (auto attr : compatibleAttrSet) {
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
    sort(matches.begin(), matches.end());
    
    return matches;
}
