#ifndef MatchMaker_h
#define MatchMaker_h

#include <vector>
#include <string>
#include <unordered_map>
#include "provided.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
using namespace std;

class MatchMaker {
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) : m_mdb(mdb), m_at(at) {}
    ~MatchMaker() {}
    
    vector<EmailCount> IdentifyRankedMatches(string email, int threshold) const;
    
private:
    const MemberDatabase& m_mdb;
    const AttributeTranslator& m_at;
};

#endif /* MatchMaker_hpp */
