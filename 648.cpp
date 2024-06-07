#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    string word;

    TrieNode() : word("") {}
};

class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        TrieNode* root = buildTrie(dictionary);
        stringstream ss(sentence);
        string word;
        string result = "";

        while (ss >> word) {
            if (!result.empty()) {
                result += " ";
            }

            TrieNode* node = root;
            for (char c : word) {
                if (node->children.find(c) == node->children.end() || !node->word.empty()) {
                    break;
                }
                node = node->children[c];
            }

            result += node->word.empty() ? word : node->word;
        }

        return result;
    }

private:
    TrieNode* buildTrie(vector<string>& words) {
        TrieNode* root = new TrieNode();
        for (const string& word : words) {
            TrieNode* node = root;
            for (char c : word) {
                if (node->children.find(c) == node->children.end()) {
                    node->children[c] = new TrieNode();
                }
                node = node->children[c];
            }
            node->word = word;
        }
        return root;
    }
};

int main() {
    Solution solution;
    vector<string> dictionary1 = {"cat", "bat", "rat"};
    string sentence1 = "the cattle was rattled by the battery";
    cout << solution.replaceWords(dictionary1, sentence1) << endl;  // Output: "the cat was rat by the bat"

    vector<string> dictionary2 = {"a", "b", "c"};
    string sentence2 = "aadsfasf absbs bbab cadsfafs";
    cout << solution.replaceWords(dictionary2, sentence2) << endl;  // Output: "a a b c"

    return 0;
}
