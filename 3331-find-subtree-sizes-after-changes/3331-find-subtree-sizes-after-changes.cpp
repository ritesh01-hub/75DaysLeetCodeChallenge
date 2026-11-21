
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);

        // Build original tree
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> newParent(n, -1);
        vector<int> last(26, -1);

        // Step 1: Find new parents using original tree
        function<void(int)> dfs1 = [&](int u) {
            int ch = s[u] - 'a';

            int previous = last[ch];

            if (previous != -1) {
                newParent[u] = previous;
            } else {
                newParent[u] = parent[u];
            }

            last[ch] = u;

            for (int v : adj[u]) {
                dfs1(v);
            }

            // Backtrack
            last[ch] = previous;
        };

        dfs1(0);

        // Step 2: Build modified tree
        vector<vector<int>> newAdj(n);

        for (int i = 1; i < n; i++) {
            newAdj[newParent[i]].push_back(i);
        }

        // Step 3: Calculate subtree sizes
        vector<int> ans(n, 1);

        function<void(int)> dfs2 = [&](int u) {
            for (int v : newAdj[u]) {
                dfs2(v);
                ans[u] += ans[v];
            }
        };

        dfs2(0);

        return ans;
    }
};
