#ifndef MemberDatabase_h
#define MemberDatabase_h

#include <string>
#include <vector>
#include "PersonProfile.h"
#include "RadixTree.h"
using namespace std;

class MemberDatabase {
public:
    MemberDatabase() {} //TODO: ctor
    ~MemberDatabase() {} //TODO: dtor
    
    bool LoadDatabase(string filename);
    vector<string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(string email) const;
};

#endif /* MemberDatabase_hpp */

