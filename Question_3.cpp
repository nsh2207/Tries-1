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
void addWord(Node* root, string word){
    Node* ptr = root;
    for(auto c:word){
        if(!ptr->neighbors[c-'a']) ptr->neighbors[c-'a'] = get_node();
        ptr = ptr->neighbors[c-'a'];
    }
    ptr->is_word = true;
}
string findRoot(Node* root, string word){
    Node* ptr = root;
    string prefix;
    for(auto c:word){
        prefix.push_back(c);
        if(!ptr->neighbors[c-'a']) return word;
        if(ptr->neighbors[c-'a']->is_word) return prefix; 
        ptr = ptr->neighbors[c-'a'];
    }
    return word;
}
class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        Node* root = get_node();
        for(auto word:dictionary){
            addWord(root, word);
        }
        vector<string>words;
        string currWord;
        for(auto c:sentence){
            if(c==' '){
                words.push_back(currWord);
                currWord.clear();
            }
            else{
                currWord.push_back(c);
            }
        }
        words.push_back(currWord);
        string finalSentence;
        for(auto word:words){
            string processed = findRoot(root, word);
            finalSentence.insert(finalSentence.end(), processed.begin(),processed.end());
            finalSentence.push_back(' ');
        }
        finalSentence.pop_back();
        return finalSentence;
    }
};
int main() {
    Solution solution;
    vector<string> dictionary = {"cat", "bat", "rat"};
    string sentence = "the cattle was rattled by the battery";
    string result = solution.replaceWords(dictionary, sentence);
    cout << "Processed sentence: " << result << endl; // Output: "the cat was rat by the bat"
    return 0;
}
// // Time Complexity: O(m*n + p*k) where m is the number of words in the dictionary, n is the average length of the words in the dictionary, p is the number of words in the sentence, and k is the average length of the words in the sentence
// // Space Complexity: O(m*n) for storing the Trie
// // Did this code successfully run on Leetcode: Yes
// // Any problem you faced while coding this: No
// // Your code here along with comments explaining your approach in three sentences only
// Prepared a Trie data structure and populated it with the given dictionary words. Then for each word in the sentence, I searched for the shortest prefix in the Trie and replaced the word with that prefix if found. Finally, I constructed the processed sentence by joining the modified words.