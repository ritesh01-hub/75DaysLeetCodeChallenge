class Solution {
public:
    // Trie Node
    struct TrieNode {
        TrieNode* children[26] = {};
        string word = ""; // stores complete word at end node
    };

    TrieNode* root;

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int i = c - 'a';
            if (!node->children[i])
                node->children[i] = new TrieNode();
            node = node->children[i];
        }
        node->word = word; // mark end of word
    }

    void dfs(vector<vector<char>>& board, int r, int c, TrieNode* node, vector<string>& res) {
        char ch = board[r][c];

        // pruning: if char not in trie path, stop
        if (ch == '#' || !node->children[ch - 'a']) return;

        node = node->children[ch - 'a'];

        // found a complete word
        if (!node->word.empty()) {
            res.push_back(node->word);
            node->word = ""; // avoid duplicates
        }

        board[r][c] = '#'; // mark visited

        int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
        for (auto& d : dirs) {
            int nr = r + d[0], nc = c + d[1];
            if (nr >= 0 && nr < board.size() && nc >= 0 && nc < board[0].size())
                dfs(board, nr, nc, node, res);
        }

        board[r][c] = ch; // restore
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        root = new TrieNode();
        for (auto& w : words) insert(w);

        vector<string> res;
        for (int i = 0; i < board.size(); i++)
            for (int j = 0; j < board[0].size(); j++)
                dfs(board, i, j, root, res);

        return res;
    }
};