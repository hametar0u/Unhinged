//main.cpp

#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"
#include "provided.h"
#include "RadixTree.h" //TODO: remove?
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

const std::string MEMBERS_FILE    = "/Users/bigsad/Desktop/UCLA/CS/CS32/Unhinged/Unhinged/membersTest.txt";
const std::string TRANSLATOR_FILE = "/Users/bigsad/Desktop/UCLA/CS/CS32/Unhinged/Unhinged/translator.txt";

bool findMatches(/*const*/ MemberDatabase& mdb, const AttributeTranslator& at);

int main() {
//    RadixTree<AttValPair> r;
//    AttValPair a("hobby", "coding");
//    r.insert("hobby", a);
//    a = AttValPair("hobby", "affairs");
//    r.insert("hobby", a);
//    AttValPair* ent = r.search("hobby");
//    cerr << ent->attribute << "," << ent->value << endl;
//    ent->value = "eating";
//    ent = r.search("hobby");
//    cerr << ent->attribute << "," << ent->value << endl;
//
//    PersonProfile p("David", "david@david.com");
//    assert(p.GetNumAttValPairs() == 0);
//    p.AddAttValPair(a);
//    assert(p.GetNumAttValPairs() == 1);
//    assert(p.GetAttVal(0, a) == true);
//    cerr << a.attribute << "," << a.value << endl;
    
    AttributeTranslator at;
    at.Load("/Users/bigsad/Desktop/UCLA/CS/CS32/Unhinged/Unhinged/translator.txt");
    AttValPair a("hobby", "rock climbing");
    vector<AttValPair> v = at.FindCompatibleAttValPairs(a);
    cout << v.size() << " compatible pairs" << endl;
    
    
//    MemberDatabase mdb;
//    if (!mdb.LoadDatabase(MEMBERS_FILE))
//    {
//        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
//        return 1;
//    }
//    AttributeTranslator at;
//    if (!at.Load(TRANSLATOR_FILE))
//    {
//        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
//        return 1;
//    }
//
//    while (findMatches(mdb, at))
//        ;
//
//    std::cout << "Happy dating!" << std::endl;
}

bool findMatches(/*const*/ MemberDatabase& mdb, /*const*/ AttributeTranslator& at)
{
      // Prompt for email
    std::string email;
    const PersonProfile* pp;
    for (;;) {
        std::cout << "Enter the member's email for whom you want to find matches: ";
        std::getline(std::cin, email);
        if (email.empty())
            return false;
        pp = mdb.GetMemberByEmail(email);
        if (pp != nullptr)
            break;
        std::cout << "That email is not in the member database." << std::endl;
    }

      // Show member's attribute-value pairs
    std::cout << "The member has the following attributes:" << std::endl;
    for (int k = 0; k != pp->GetNumAttValPairs(); k++) {
        AttValPair av;
        pp->GetAttVal(k, av);
        std::cout << av.attribute << " --> " << av.value << std::endl;
    }
    
    AttValPair test("trait","uncritical");
    vector<string> vec = mdb.FindMatchingMembers(test);
    cout << "uncritical buffoons: " << vec.size() << endl;

      // Prompt user for threshold
    int threshold;
    std::cout << "How many shared attributes must matches have? ";
    std::cin >> threshold;
    std::cin.ignore(10000, '\n');

      // Print matches and the number of matching translated attributes
    MatchMaker mm(mdb, at);
    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
    if (emails.empty())
        std::cout << "No member was a good enough match." << std::endl;
    else {
        std::cout << "The following members were good matches:" << std::endl;;
        for (const auto& emailCount : emails) {
            const PersonProfile* pp = mdb.GetMemberByEmail(emailCount.email);
            std::cout << pp->GetName() << " at " << emailCount.email << " with "
                      << emailCount.count << " matches!" << std::endl;
        }
    }
    std::cout << std::endl;
    return true;
}
