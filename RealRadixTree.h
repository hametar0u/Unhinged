#ifndef RealRadixTree_h
#define RealRadixTree_h

#include <vector>
#include <string>
using namespace std;

//constants
const int CHILDREN_SIZE = 128; //# ASCII characters
enum caseNum {TRAILING_KEY, TRAILING_LABEL, MID_SPLIT, NO_COMMON_SUBSTR};

//radixtree class
template <typename ValueType>
class RadixTree {
public:
    RadixTree() : m_size(0) {
        root = new Node;
    }
    
    ~RadixTree() {
        burnDownTree(root);
    }
    
    void insert(string key, const ValueType& value) {
        /*
         insert case examples:
         NO_COMMON_SUBSTR: cat -> winter
         TRAILING_KEY: ca -> cat
         TRAILING_LABEL: cat -> ca
         MID_SPLIT: cat -> cyan
         */
        
        //get position to insert
        caseNum caseType;
        Node* target = findFirstNonMatching(root, caseType, key);
        if (!target) return; //key in tree already
        
        //deal with insert cases
        switch(caseType) {
            case NO_COMMON_SUBSTR: {
                int index = key[0];
                Node* n = new Node(key, value);
                target->children[index] = n; //insert node into index of the ascii character of key[0]
                return;
                break; //extraneous but failsafe
            }
            case TRAILING_KEY: {
                /*
                 use label in target to figure out the remaining key
                 insert in right spot
                 */
                string remainingKey = key.substr(target->label.size());
                int index = remainingKey[0];
                Node* n = new Node(remainingKey, value);
                target->children[index] = n;
                return;
                break;
            }
            case TRAILING_LABEL: {
                string remainingLabel = target->label.substr(key.size()); //take leftover chars in label
                int index = remainingLabel[0];
                
                Node* n = new Node(*target, remainingLabel); //inherit everything in parent except the label
                killChildren(target); //wipe parent's children (we don't wipe parent value because ValueType is templated)
                target->children[index] = n;
                
                target->val = value; //set parent value to passed in value
                target->label = key; //set parent label to key
                //end is still true so no need to do anything
                
                return;
                break;
            }
            case MID_SPLIT: {
                string common; //find all common letters
                int i = 0;
                int j = 0;
                while (target->label[i] != key[j]) {
                    j++;
                }
                key = key.substr(j); //splice off the beginning that may be used in parent nodes
                while (target->label[i] == key[i]) {
                    common += key[i];
                    i++;;
                }
                //get the leftover characters in label and key
                string remainingLabel = target->label.substr(i);
                string remainingKey = key.substr(i);
                int index1 = remainingLabel[0];
                int index2 = remainingKey[0];
                
                Node* n1 = new Node(*target, remainingLabel); //inherit everything from parent
                killChildren(target);
                
                Node* n2 = new Node(remainingKey, value); //new node with the passed in stuff
                
                target->children[index1] = n1;
                target->children[index2] = n2;
                target->label = common; //change parent label to the common substring
                target->end = false;
                
                return;
                break;
            }
        }
        
    }
    
    ValueType* search(string key) const {
        if (key.size() == 0) return nullptr;
        return searchHelper(key, root);
    }
    
private:
    struct Node {
        Node() {
            label = "";
            for (int i = 0; i < CHILDREN_SIZE; i++) {
                children[i] = nullptr;
            }
            end = false;
        }
        
        Node(const Node& src, const string key) { //cpy ctor except we modify the label
            label = key;
            for (int i = 0; i < CHILDREN_SIZE; i++) {
                children[i] = src.children[i];
            }
            val = src.val;
            end = src.end;
        }
        
        Node(const string key, const ValueType& value) {
            label = key;
            val = value;
            for (int i = 0; i < CHILDREN_SIZE; i++) {
                children[i] = nullptr;
            }
            end = true;
        }

        string label;
        ValueType val;
        Node* children[CHILDREN_SIZE];
        bool end;
    };
    
    //helper functions
    ValueType* searchHelper(string key, Node* root) const {
        
        /*
         start at root
         get key[0] and go to children[ASCII value]
         if (!c) your search failed so you return nullptr
         else, follow c into child
         
         compare label.substr(1) to same amount of letters in remaining key
         if matched, check if anything left in key
         if no, return &value
         else, take first letter of next part and go to children[ASCII value]
         
         loop
         
         base case:
         if !curPtr return nullptr
         */
        
        if (!root) return nullptr; //base case:
        Node* cur = root;
        
        int index = key[0]; //get first char and go to the corresponding index
        if (!cur->children[index]) return nullptr; //your search failed so you return nullptr
        cur = cur->children[index]; //follow into child
        
        string partOfKey = key.substr(0, cur->label.size());
        if (partOfKey != cur->label) return nullptr;
        
        if (key.size() == cur->label.size() && cur->end) return &cur->val; //perfect match, so return the value
        
        string remainingKey = key.substr(cur->label.size());
        
        return searchHelper(remainingKey, cur);
    }
    
    Node* findFirstNonMatching(Node* root, caseNum& caseType, string key) {
        if (!root) return nullptr; //base case:
        Node* cur = root;
        
        int index = key[0]; //get first char and go to the corresponding index
        if (!cur->children[index]) {
            caseType = NO_COMMON_SUBSTR; //you didn't find anything so your first node is non matching
            return cur;
        }
        cur = cur->children[index]; //follow into child
        
        
        if (key == cur->label) return nullptr; //perfect match, so return nothing
        if (cur->label.size() > key.size()) {
            string partOfLabel = cur->label.substr(0, key.size());
            if (partOfLabel != key) {
                caseType = MID_SPLIT;
                return cur;
            }
            else {
                caseType = TRAILING_LABEL;
                return cur;
            }
        }
        
        //if label size < key size
        string partOfKey = key.substr(0, cur->label.size());
        if (partOfKey != cur->label) {
            caseType = MID_SPLIT; //first char is guaranteed to be the same due to above check
            return cur;
        }
            

        string remainingKey = key.substr(cur->label.size());
        index = remainingKey[0];
        if (!cur->children[index]) {
            caseType = TRAILING_KEY; //there's only stuff left in the key
            return cur;
        }
        
        return findFirstNonMatching(cur, caseType, remainingKey);
    }
    
    void killChildren(Node* target) {
        for (int i = 0; i < CHILDREN_SIZE; i++) {
            target->children[i] = nullptr;
        }
    }
    
    void burnDownTree(Node* root) {
        for (int i = 0; i < CHILDREN_SIZE; i++) {
            if (!root->children[i]) continue;
            burnDownTree(root->children[i]);
        }
        
        delete root;
    }
    
    Node* root;
    int m_size;
};

#endif /* RealRadixTree_h */
