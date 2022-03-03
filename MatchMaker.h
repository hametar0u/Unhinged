#ifndef MatchMaker_h
#define MatchMaker_h

#include <vector>
#include <string>
#include "provided.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
using namespace std;

class MatchMaker {
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) {} //TODO: ctor
    ~MatchMaker() {} //TODO: dtor
    
    vector<EmailCount> IdentifyRankedMatches(string email, int threshold) const;
};

#endif /* MatchMaker_hpp */
