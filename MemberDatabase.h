#ifndef MemberDatabase_h
#define MemberDatabase_h

#include <string>
#include <vector>
#include <unordered_set>
#include "PersonProfile.h"
#include "RadixTree.h"
using namespace std;

class MemberDatabase {
public:
    MemberDatabase() {}
    ~MemberDatabase() {
        for (auto profile : profiles) {
            delete profile;
        }
    }
    
    bool LoadDatabase(string filename);
    vector<string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(string email) const;
    
private:
    struct emailPair {
        emailPair() {}
        emailPair(string email) {
            s.insert(email);
            v.push_back(email);
        }
        unordered_set<string> s;
        vector<string> v;
    };
    
    RadixTree<PersonProfile*> profilesByEmail;
    RadixTree<emailPair> emailsByAttrVal;
    vector<PersonProfile*> profiles;
};

#endif /* MemberDatabase_hpp */

