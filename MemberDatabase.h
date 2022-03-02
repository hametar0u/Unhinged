//
//  MemberDatabase.hpp
//  Unhinged
//
//  Created by Big Sad on 2022-03-02.
//

#ifndef MemberDatabase_h
#define MemberDatabase_h

#include <string>
#include <vector>
#include "PersonProfile.h"
using namespace std;

class MemberDatabase {
public:
    MemberDatabase();
    ~MemberDatabase() {}
    
    bool LoadDatabase(string filename);
    vector<string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(string email) const;
};

#endif /* MemberDatabase_hpp */
