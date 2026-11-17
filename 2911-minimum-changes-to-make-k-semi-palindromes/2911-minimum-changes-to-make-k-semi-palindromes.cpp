
class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();

        // cost[i][j] = minimum changes to make s[i...j]
        // a semi-palindrome
        vector<vector<int>> cost(n, vector<int>(n, 1e9));

        // Precompute minimum changes for every substring
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len <= n; i++) {
                int j = i + len - 1;

                // Try every proper divisor of substring length
                for (int d = 1; d < len; d++) {
                    if (len % d != 0) continue;

                    int changes = 0;

                    // Compare symmetric characters
                    // in each group of step d
                    for (int r = 0; r < d; r++) {
                        int l = i + r;
                        int right = j - ((len - 1 - r) % d);

                        // Count each pair only once
                        while (l < right) {
                            if (s[l] != s[right])
                                changes++;

                            l += d;
                            right -= d;
                        }
                    }

                    cost[i][j] = min(cost[i][j], changes);
                }
            }
        }

        // dp[i][parts] = minimum changes to partition
        // first i characters into parts substrings
        vector<vector<int>> dp(n + 1,
                               vector<int>(k + 1, 1e9));

        dp[0][0] = 0;

        for (int parts = 1; parts <= k; parts++) {
            for (int i = 2 * parts; i <= n; i++) {
                for (int j = 2 * (parts - 1); j <= i - 2; j++) {
                    dp[i][parts] = min(
                        dp[i][parts],
                        dp[j][parts - 1] + cost[j][i - 1]
                    );
                }
            }
        }

        return dp[n][k];
    }
};
