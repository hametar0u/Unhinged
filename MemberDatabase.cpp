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
        istringstream iss(line);
        string name;
        string email;
        string num;
        int numPairs;
        //getline succeeds if it gets at least one character (doesn't matter if there's no ,)
        if (!getline(iss, name)) return false;
        if (!getline(iss, email)) return false;
        PersonProfile member(name, email);
        profilesByEmail.insert(email, &member);
        
        if (!getline(iss, num)) return false;
        numPairs = stoi(num);
        for (int i = 0; i < numPairs; i++) {
            string attr; string val;
            if (!getline(iss, attr, ',')) return false;
            if (!getline(iss, val, ',')) return false;
            
            string pair = attr + "," + val;
            AttValPair attval(attr, val);
            
            member.AddAttValPair(attval);
            
            emailsByAttrVal.insert(pair, email);
        }
    
    }
    
    
    return true; //TODO: implement
}
vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
    return {}; //TODO: implement
}
const PersonProfile* MemberDatabase::GetMemberByEmail(string email) const {
    PersonProfile* temp = nullptr;
    return temp; //TODO: implement
}
