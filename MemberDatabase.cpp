#include "MemberDatabase.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "utility.h"
using namespace std;

bool MemberDatabase::LoadDatabase(string filename) {
    ifstream file(filename);
    if (!file) return false;
    
    string line;
    while (getline(file, line)) { //gets name
        string name = line;
        string email;
        string num;
        int numPairs;
        //getline succeeds if it gets at least one character (doesn't matter if there's no ,)
        if (!getline(file, email)) return false; //gets email
        PersonProfile* member = new PersonProfile(name, email);
//        PersonProfile member(name, email);
        
        if (!getline(file, num)) return false;
        numPairs = stoi(num);
        for (int i = 0; i < numPairs; i++) {
            string attr; string val;
            string pair; //attval pair string
            getline(file, pair);
            istringstream iss(pair);
            if (!getline(iss, attr, ',')) return false;
            if (!getline(iss, val, ',')) return false;
            
            AttValPair attval(attr, val);
            
            member->AddAttValPair(attval);
//            member.AddAttValPair(attval);
            
            emailPair* emailsWithAttval = emailsByAttrVal.search(pair);
            if (emailsWithAttval == nullptr) {
                emailPair e(email);
                emailsByAttrVal.insert(pair, e);
            }
            else {
                if (emailsWithAttval->s.insert(email).second) {
                    emailsWithAttval->v.push_back(email);
                }
            }
        }
        
        
        profilesByEmail.insert(email, member);
        
        string junk;
        getline(file, junk); //to skip the br between each entry
    
    }
    
    
    return true;
}
vector<string> MemberDatabase::FindMatchingMembers(/*const*/ AttValPair& input) /*const*/ {
    string pair = attVal2Str(input.attribute, input.value);
    emailPair* matchingVec = emailsByAttrVal.search(pair);
    if (!matchingVec) return {};
    return matchingVec->v;
    
}
/*const*/ PersonProfile* MemberDatabase::GetMemberByEmail(string email) /*const*/ {
    PersonProfile** target = profilesByEmail.search(email);
//    return target;
    return !target ? nullptr : *target;
}
