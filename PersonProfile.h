#ifndef PersonProfile_h
#define PersonProfile_h

#include <string>
#include <unordered_set>
#include <vector>
#include "provided.h"
#include "RadixTree.h"
using namespace std;

class PersonProfile {
public:
    PersonProfile(string name, string email) : m_name(name), m_email(email), m_numPairs(0) {}
    ~PersonProfile() {}
    
    string GetName() const { return m_name; }
    string GetEmail() const { return m_email; }
    
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
    
private:
    string m_name;
    string m_email;
    int m_numPairs;
    RadixTree<string> t;
    unordered_set<string> s;
    vector<AttValPair> v;
};

#endif /* PersonProfile_hpp */
