#include<vector>
#include<string>
#include<iostream>
using namespace std;
struct Node{
    bool is_word;
    vector<Node*>neighbors;
};
Node* get_node(){
    Node* node = new Node();
    node->is_word = false;
    node->neighbors = vector<Node*>(26,NULL);
    return node;
}
class Trie {
private:
    Node* root;
public:
    Trie() {
        root = get_node();
    }
    
    void insert(string word) {
        Node* ptr = root;
        for(auto c:word){
            if(!ptr->neighbors[c-'a']) ptr->neighbors[c-'a'] = get_node();
            ptr = ptr->neighbors[c-'a'];
        }
        ptr->is_word = true;
    }
    
    bool search(string word) {
        Node* ptr = root;
        for(auto c:word){
            if(!ptr->neighbors[c-'a']) return false;
            ptr = ptr->neighbors[c-'a'];
        }
        return ptr->is_word;
    }
    
    bool startsWith(string prefix) {
        Node* ptr = root;
        for(auto c:prefix){
            if(!ptr->neighbors[c-'a']) return false;
            ptr = ptr->neighbors[c-'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
int main() {
    Trie* obj = new Trie();
    obj->insert("apple");
    cout<<obj->search("apple")<<endl; // true
    cout<<obj->search("app")<<endl; // false
    cout<<obj->startsWith("app")<<endl; // true
    obj->insert("app");
    cout<<obj->search("app")<<endl; // true
    return 0;
}
// Time Complexity: O(m) for insert, search, and startsWith operations, where m is the length of the word or prefix.
// Space Complexity: O(m) for each word inserted in the trie, where m is the length of the word.
// Did this code successfully run on Leetcode: Yes
// Any problem you faced while coding this: No
// Your code here along with comments explaining your approach in three sentences only
// Implemented a Trie data structure using a Node struct that contains a boolean to indicate if it's the end of a word and a vector of pointers to its children. The insert method adds words to the trie, while the search and startsWith methods check for the existence of words and prefixes, respectively. Each operation traverses the trie based on the characters of the input string.