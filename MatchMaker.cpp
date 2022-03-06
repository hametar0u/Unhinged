#include "MatchMaker.h"
#include <algorithm>

vector<EmailCount> MatchMaker::IdentifyRankedMatches(string email, int threshold) /*const*/ {
    
//    unordered_set<AttValPair> compatibleAttrSet;
    unordered_map<string, int> emailCounts;
    vector<EmailCount> matches;
    vector<AttValPair> compatibleAttr;
    
    PersonProfile* member = m_mdb.GetMemberByEmail(email);
    if (!member) return {};
    
    for (int i = 0; i < member->GetNumAttValPairs(); i++) {
        AttValPair member_attr;
        member->GetAttVal(i, member_attr);
        appendVector(compatibleAttr, m_at.FindCompatibleAttValPairs(member_attr));
//        for (auto attr : compatibleAttr) {
//            compatibleAttrSet.insert(attr);
//        }
        
    }
    for (auto attr : compatibleAttr) {
        vector<string> matchingMembers = m_mdb.FindMatchingMembers(attr);
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
