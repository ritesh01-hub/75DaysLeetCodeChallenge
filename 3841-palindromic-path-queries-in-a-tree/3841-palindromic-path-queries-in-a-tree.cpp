class Solution {
    vector<vector<int>> adj;
    vector<vector<int>> up;
    vector<int> tin, tout, depth;
    vector<int> bit;
    string s;
    int timer, LOG;

    void dfs(int u, int p) {
        tin[u] = ++timer;
        up[0][u] = p;

        for (int i = 1; i < LOG; i++) {
            up[i][u] = up[i - 1][up[i - 1][u]];
        }

        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }

        tout[u] = timer;
    }

    void updateBIT(int i, int val) {
        for (; i < (int)bit.size(); i += i & -i) {
            bit[i] ^= val;
        }
    }

    int queryBIT(int i) {
        int res = 0;
        for (; i > 0; i -= i & -i) {
            res ^= bit[i];
        }
        return res;
    }

    int getMask(int u) {
        return queryBIT(tin[u]);
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        int diff = depth[u] - depth[v];

        for (int i = 0; i < LOG; i++) {
            if (diff & (1 << i)) {
                u = up[i][u];
            }
        }

        if (u == v) return u;

        for (int i = LOG - 1; i >= 0; i--) {
            if (up[i][u] != up[i][v]) {
                u = up[i][u];
                v = up[i][v];
            }
        }

        return up[0][u];
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        this->s = s;
        adj.assign(n, {});
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        up.assign(LOG, vector<int>(n, 0));
        tin.assign(n, 0);
        tout.assign(n, 0);
        depth.assign(n, 0);
        bit.assign(n + 2, 0);
        timer = 0;

        dfs(0, 0);

     
        for (int u = 0; u < n; u++) {
            int mask = 1 << (s[u] - 'a');
            updateBIT(tin[u], mask);
            updateBIT(tout[u] + 1, mask);
        }

        vector<bool> ans;

        for (string& q : queries) {
            stringstream ss(q);
            string type;
            ss >> type;

            if (type == "update") {
                int u;
                char c;
                ss >> u >> c;

                int oldMask = 1 << (s[u] - 'a');
                int newMask = 1 << (c - 'a');

                updateBIT(tin[u], oldMask ^ newMask);
                updateBIT(tout[u] + 1, oldMask ^ newMask);

                s[u] = c;
            } else {
                int u, v;
                ss >> u >> v;

                int w = lca(u, v);

                int mask =
                    getMask(u) ^ getMask(v) ^
                    (1 << (s[w] - 'a'));

               
                if (__builtin_popcount((unsigned)mask) <= 1) {
                    ans.push_back(true);
                } else {
                    ans.push_back(false);
                }
            }
        }

        return ans;
    }
};