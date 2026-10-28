class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // dp[j][x] = whether XOR value x is possible
        // for the current row at column j
        vector<vector<bool>> dp(n, vector<bool>(1024, false));

        dp[0][grid[0][0]] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                vector<bool> cur(1024, false);

                // From top
                if (i > 0) {
                    for (int x = 0; x < 1024; x++) {
                        if (dp[j][x]) {
                            cur[x ^ grid[i][j]] = true;
                        }
                    }
                }

                // From left
                if (j > 0) {
                    for (int x = 0; x < 1024; x++) {
                        if (dp[j - 1][x]) {
                            cur[x ^ grid[i][j]] = true;
                        }
                    }
                }

                dp[j] = cur;
            }
        }

        // Find minimum possible XOR at bottom-right
        for (int x = 0; x < 1024; x++) {
            if (dp[n - 1][x])
                return x;
        }

        return -1;
    }
};