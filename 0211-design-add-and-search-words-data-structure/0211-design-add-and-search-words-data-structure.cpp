class WordDictionary {
private:
    struct TrieNode {
        TrieNode* children[26];
        bool isEnd;

        TrieNode() {
            isEnd = false;
            for(int i = 0; i < 26; i++) {
                children[i] = NULL;
            }
        }
    };

    TrieNode* root;

public:
    WordDictionary() {
        root = new TrieNode();
    }

    void addWord(string word) {
        TrieNode* node = root;

        for(char c : word) {
            int idx = c - 'a';
            if(node->children[idx] == NULL) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
        }

        node->isEnd = true;
    }

    bool search(string word) {
        return dfs(word, 0, root);
    }

private:
    bool dfs(string &word, int i, TrieNode* node) {
        if(node == NULL) return false;

        if(i == word.size()) {
            return node->isEnd;
        }

        if(word[i] == '.') {
            // try all possible paths
            for(int j = 0; j < 26; j++) {
                if(node->children[j] && dfs(word, i + 1, node->children[j])) {
                    return true;
                }
            }
            return false;
        } else {
            int idx = word[i] - 'a';
            return dfs(word, i + 1, node->children[idx]);
        }
    }
};