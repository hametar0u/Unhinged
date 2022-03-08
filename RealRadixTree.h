#ifndef RealRadixTree_h
#define RealRadixTree_h

#include <vector>
#include <string>
using namespace std;

const int CHILDREN_SIZE = 128; //TODO: change this number

template <typename ValueType>
class RadixTree {
public:
    RadixTree() : m_size(0) {
        root = new Node;
    }
    
    ~RadixTree() {}
    
    //starting with just lowercase alphabets
    void insert(string key, const ValueType& value) {
        
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
        
        //helper function
        const ValueType* searchHelper(string key, Node* root) const {
            
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
        
        string label;
        ValueType val;
        Node* children[CHILDREN_SIZE];
        bool end;
    };
    
    Node* root;
    int m_size;
};

#endif /* RealRadixTree_h */
