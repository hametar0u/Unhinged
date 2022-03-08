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
        killTree(root);
    }
    
    //starting with just lowercase alphabets
    void insert(string key, const ValueType& value) {
        /*
         first get the position to insert
         then deal with the insert cases
         
         NO_COMMON_SUBSTR: cat -> winter
         TRAILING_KEY: ca -> cat
         TRAILING_LABEL: cat -> ca
         MID_SPLIT: cat -> cyan
         */
        
        caseNum caseType;
        Node* target = findFirstNonMatching(root, caseType, key);
        if (!target) return;
        
        switch(caseType) {
            case NO_COMMON_SUBSTR: {
                /*
                 find ascii character of key[0] and insert the node
                 */
                int index = key[0];
                Node* n = new Node;
                n->label = key;
                n->val = value;
                target->children[index] = n;
                return;
                break; //extraneous but failsafe
            }
            case TRAILING_KEY: {
                /*
                 use label in target to figure out the remaining key
                 insert in right spot
                 */
                string remainingKey = key.substr(target->label.size() + 1);
                int index = remainingKey[0];
                Node* n = new Node;
                n->label = key;
                n->val = value;
                target->children[index] = n;
                return;
                break;
            }
            case TRAILING_LABEL: {
                /*
                 take leftover words in label
                 create new node that inherits everything in parent
                 wipe parent's children (we don't wipe parent value because ValueType is templated)
                 parent point to new node
                 set parent value to passed in value
                 change parent name to label
                 make sure to keep the actual boolean true
                 */
                string remainingLabel = target->label.substr(key.size() + 1);
                int index = remainingLabel[0];
                
                Node* n = new Node(*target); //cpy ctor
                killChildren(target);
                target->children[index] = n;
                
                target->val = value;
                target->label = key;
                
                return;
                break;
            }
            case MID_SPLIT: {
                /*
                 find all of common letters
                 take leftover words
                 inherit everything in parent including boolean
                 wipe
                 parent point to new node
                 insert new node with whatever is left in the key
                 parent point to new node
                 change parent label to common words
                 */
                string common;
                int i = 0;
                while (target->label[i] == key[i]) {
                    common += key[i];
                    i++;
                }
                string remainingLabel = target->label.substr(i);
                string remainingKey = key.substr(i);
                int index1 = remainingLabel[0];
                int index2 = remainingKey[0];
                
                Node* n1 = new Node(*target);
                n1->label = remainingLabel; //the cpy ctor inherits the original label so I need to overwrite it
                killChildren(target);
                
                Node* n2 = new Node;
                n2->label = remainingKey;
                n2->val = value;
                
                target->children[index1] = n1;
                target->children[index2] = n2;
                target->label = common;
                
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
        
        Node(const Node& src) {
            label = src.label;
            for (int i = 0; i < CHILDREN_SIZE; i++) {
                children[i] = src.children[i];
            }
            end = src.end;
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
        
        if (key.size() == cur->label.size()) return &cur->val; //perfect match, so return the value
        
        string remainingKey = key.substr(cur->label.size() + 1);
        
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
        
        
        if (key.size() == cur->label.size()) return nullptr; //perfect match, so return nothing
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
            

        string remainingKey = key.substr(cur->label.size() + 1); //TODO: not needed??
        caseType = TRAILING_KEY; //there's only stuff left in the key
        return cur;
        
        return findFirstNonMatching(cur, caseType, remainingKey);
    }
    
    void killChildren(Node* target) {
        for (int i = 0; i < CHILDREN_SIZE; i++) {
            target->children[i] = nullptr;
        }
    }
    
    void killTree(Node* root) {
        for (int i = 0; i < CHILDREN_SIZE; i++) {
            if (!root->children[i]) continue;
            killTree(root->children[i]);
        }
        
        delete root;
    }
    
    Node* root;
    int m_size;
};

#endif /* RealRadixTree_h */
