#include<vector>
#include<string>
#include<iostream>
using namespace std;
struct Node{
    bool is_word;
    vector<Node*>neighbors;
};
Node* get_node(bool is_word){
    Node* node = new Node();
    node->is_word = is_word;
    node->neighbors = vector<Node*>(26, NULL);
    return node;
}
void addString(Node* root, string word){
    Node* ptr = root;
    for(auto c:word){
        if(!ptr->neighbors[c-'a']) ptr->neighbors[c-'a'] = get_node(false);
        ptr = ptr->neighbors[c-'a'];
    }
    ptr->is_word = true;
}
void findLargest(Node* node, string& currWord, string& word, Node* root ){
    for(int i=0;i<=25;i++){
        if(node->neighbors[i]&&node->neighbors[i]->is_word){
            currWord.push_back('a'+i);
            if((currWord.size()>word.size())||(currWord.size()==word.size()&&currWord<word)) word = currWord;
            findLargest(node->neighbors[i], currWord, word, root);
            currWord.pop_back();
        }
    }
}
class Solution {
public:
    string longestWord(vector<string>& words) {
        Node* root = get_node(false);
        for(auto word:words) addString(root, word);
        string currWord, word;
        findLargest(root, currWord, word, root);
        return word;
    }
};
int main() {
    Solution solution;
    vector<string> words = {"w","wo","wor","worl", "world"};
    string result = solution.longestWord(words);
    cout << "Longest word: " << result << endl; // Output: world
    return 0;
}
// Time Complexity: O(m*n) where m is the number of words and n is the average length of the words
// Space Complexity: O(m*n) for storing the Trie
// Did this code successfully run on Leetcode: Yes
// Any problem you faced while coding this: No
// Your code here along with comments explaining your approach in three sentences only
// Prepared a Trie data structure and populated it with the given words. Then I performed a DFS on the Trie tree such that I only considered the nodes with having boolean flag value as true and kept track of the lngest possible word being formed