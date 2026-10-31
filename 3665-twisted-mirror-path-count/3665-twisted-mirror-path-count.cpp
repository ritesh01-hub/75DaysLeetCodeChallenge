class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();

        vector<vector<array<int, 2>>> nxt(
            m, vector<array<int, 2>>(n, {-1, -1})
        );

        // Precompute mirror transitions
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {

                if (grid[i][j] == 0) {
                    int id = i * n + j;

                    nxt[i][j][0] = id;
                    nxt[i][j][1] = id;
                }
                else {
                    // Entering mirror from left (moving right)
                    if (i + 1 < m) {
                        nxt[i][j][0] = nxt[i + 1][j][1];
                    }

                    // Entering mirror from above (moving down)
                    if (j + 1 < n) {
                        nxt[i][j][1] = nxt[i][j + 1][0];
                    }
                }
            }
        }

        vector<vector<int>> dp(m, vector<int>(n, 0));

        dp[0][0] = 1;

        // Count paths
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (dp[i][j] == 0) continue;

                // Move right
                if (j + 1 < n) {
                    int id = nxt[i][j + 1][0];

                    if (id != -1) {
                        int x = id / n;
                        int y = id % n;

                        dp[x][y] = (dp[x][y] + dp[i][j]) % MOD;
                    }
                }

                // Move down
                if (i + 1 < m) {
                    int id = nxt[i + 1][j][1];

                    if (id != -1) {
                        int x = id / n;
                        int y = id % n;

                        dp[x][y] = (dp[x][y] + dp[i][j]) % MOD;
                    }
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};