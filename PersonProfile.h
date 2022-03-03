#ifndef PersonProfile_h
#define PersonProfile_h

#include <string>
#include <set>
#include "provided.h"
#include "RadixTree.h"
using namespace std;

class PersonProfile {
public:
    PersonProfile(string name, string email) : m_name(name), m_email(email) {}
    ~PersonProfile() {}
    
    string GetName() const { return m_name; }
    string GetEmail() const { return m_email; }
    
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
    
private:
    string m_name;
    string m_email;
    set<AttValPair> m_attributes;
    //TODO: must use radixtree class to map attributes to values???
};

#endif /* PersonProfile_hpp */
