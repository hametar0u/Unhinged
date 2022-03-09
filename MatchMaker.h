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
    MatchMaker(/*const*/ MemberDatabase& mdb, /*const*/ AttributeTranslator& at) : m_mdb(mdb), m_at(at) {}
    ~MatchMaker() {} //TODO: dtor
    
    vector<EmailCount> IdentifyRankedMatches(string email, int threshold) /*const*/;
    
private:
    void appendVector(vector<AttValPair>& a, const vector<AttValPair>& b) {
        for (auto i : b) {
            a.push_back(i);
        } //TODO: remove if not needed
    }
    
    /*const*/ MemberDatabase& m_mdb;
    /*const*/ AttributeTranslator& m_at;
};

#endif /* MatchMaker_hpp */
