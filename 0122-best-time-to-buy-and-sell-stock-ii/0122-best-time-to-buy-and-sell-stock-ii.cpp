class Solution {
public:
    int dp[100005][2];

    int f(vector<int>& prices, int i, bool on) {
        if (i == prices.size())
            return 0;

        if (dp[i][on] != -1)
            return dp[i][on];

        // Skip
        int ans = f(prices, i + 1, on);

        if (on) {
            // SELL
            ans = max(ans, prices[i] + f(prices, i + 1, false));
        } else {
            // BUY
            ans = max(ans, -prices[i] + f(prices, i + 1, true));
        }

        return dp[i][on] = ans;
    }

    int maxProfit(vector<int>& prices) {
        memset(dp, -1, sizeof(dp));
        return f(prices, 0, false);
    }
};