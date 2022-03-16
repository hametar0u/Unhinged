#ifndef RadixTree_h
#define RadixTree_h

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
    RadixTree() {
        root = new Node;
    }
    
    ~RadixTree() {
        deforestation(root);
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
        ValueType* v = search(key);
        if (v) {
            *v = value; //overwrite current value
            return;
        }
        
        caseNum caseType;
        string keyToUse;
        Node* target = findFirstNonMatching(root, caseType, key, keyToUse);
        if (!target) return; //should've been checked by above but why not
        
        //deal with insert cases
        if (keyToUse.size() != 0) key = keyToUse;
        
        switch(caseType) {
            case NO_COMMON_SUBSTR: {
                int index = key[0];
                Node* n = new Node(key, value);
                target->children[index] = n; //insert node into index of the ascii character of key[0]
                return;
                break; //extraneous but failsafe
            }
            case TRAILING_KEY: {
//                int index = keyToUse[0]; //keyToUse saves the remaining bit of the key
                int index = key[0];
                //Node* n = new Node(keyToUse, value);
                Node* n = new Node(key, value);
                target->children[index] = n;
                return;
                break;
            }
            case TRAILING_LABEL: {
//                if (keyToUse.size() != 0) key = keyToUse; //keyToUse stores the spliced key, and since its a trailing label you need to add the reamining bit of the label
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
//                if (keyToUse.size() != 0) key = keyToUse; //keyToUse only contains a value if it has to splice stuff off the front of the key because of navigating into deeper layers
                while (target->label.at(i) == key.at(i)) {
                    common += key.at(i);
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
        if (!root) return nullptr; //base case:
        Node* cur = root;
        
        int index = key[0]; //get first char and go to the corresponding index
        if (!cur->children[index]) return nullptr; //your search failed so you return nullptr
        cur = cur->children[index]; //follow into child
        
        if (key.size() < cur->label.size()) return nullptr;
        if (key == cur->label && cur->end) return &cur->val; //perfect match, so return the value
        
        string partOfKey = key.substr(0, cur->label.size());
        if (partOfKey != cur->label) return nullptr;
        
        string remainingKey = key.substr(cur->label.size());
        
        return searchHelper(remainingKey, cur);
    }
    
    Node* findFirstNonMatching(Node* root, caseNum& caseType, string key, string& keyToUse) {
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
        keyToUse = remainingKey;
        index = remainingKey[0];
        if (!cur->children[index]) {
            caseType = TRAILING_KEY; //there's only stuff left in the key
            return cur;
        }
        
        return findFirstNonMatching(cur, caseType, remainingKey, keyToUse);
    }
    
    void killChildren(Node* target) {
        for (int i = 0; i < CHILDREN_SIZE; i++) {
            target->children[i] = nullptr;
        }
    }
    
    void deforestation(Node* root) {
        for (int i = 0; i < CHILDREN_SIZE; i++) {
            if (!root->children[i]) continue;
            deforestation(root->children[i]);
        }
        
        delete root;
    }
    
    Node* root;
};

#endif /* RealRadixTree_h */
