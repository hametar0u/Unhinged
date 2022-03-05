#include "MemberDatabase.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

bool MemberDatabase::LoadDatabase(string filename) {
    ifstream file(filename);
    if (!file) return false;
    
    string line;
    while (getline(file, line)) {
        string name = line;
        string email;
        string num;
        int numPairs;
        //getline succeeds if it gets at least one character (doesn't matter if there's no ,)
        if (!getline(file, email)) return false;
//        const PersonProfile* member = new PersonProfile(name, email);
        PersonProfile member(name, email);
        profilesByEmail.insert(email, member); //<-- the data inside it get corrupted because PersonProfile was created locally
        
        if (!getline(file, num)) return false;
        numPairs = stoi(num);
        for (int i = 0; i < numPairs; i++) {
            string attr; string val;
            string pair;
            getline(file, pair);
            istringstream iss(pair);
            if (!getline(iss, attr, ',')) return false;
            if (!getline(iss, val, ',')) return false;
            
            AttValPair attval(attr, val);
            
//            member->AddAttValPair(attval);
            member.AddAttValPair(attval);
            
            unordered_set<string>* emailsWithAttval = emailsByAttrVal.search(pair);
            if (emailsWithAttval == nullptr) {
                unordered_set<string> newEmailBucket;
                newEmailBucket.insert(email);
                emailsByAttrVal.insert(pair, newEmailBucket);
            }
            else {
                emailsWithAttval->insert(email);
            }
        }
        
        string junk;
        getline(file, junk); //to skip the br between each entry
    
    }
    
    
    return true;
}
vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
    return {}; //TODO: implement
}
const PersonProfile* MemberDatabase::GetMemberByEmail(string email) /*TODO: const*/ {
    PersonProfile* target = profilesByEmail.search(email);
    return target;
//    return !target ? nullptr : target;
}
