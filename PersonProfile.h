#ifndef PersonProfile_h
#define PersonProfile_h

#include <string>
#include <set>
#include "provided.h"
using namespace std;

class PersonProfile {
public:
    PersonProfile(string name, string email) : m_name(name), m_email(email) {}
    ~PersonProfile() {}
    
    string GetName() const { return m_name; }
    string GetEmail() const { return m_email; }
    
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const { return m_attributes.size(); }
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
    
private:
    string m_name;
    string m_email;
    set<AttValPair> m_attributes;
};

#endif /* PersonProfile_hpp */
