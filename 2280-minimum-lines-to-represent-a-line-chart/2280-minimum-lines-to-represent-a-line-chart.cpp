class Solution {
public:
    int minimumLines(vector<vector<int>>& stockPrices) {

        int n = stockPrices.size();
        if (n == 1) return 0;

        sort(stockPrices.begin(), stockPrices.end());

        int lines = 1;

        for (int i = 2; i < n; i++) {

            long long dy1 = (long long)stockPrices[i - 1][1] - stockPrices[i - 2][1];
            long long dx1 = (long long)stockPrices[i - 1][0] - stockPrices[i - 2][0];

            long long dy2 = (long long)stockPrices[i][1] - stockPrices[i - 1][1];
            long long dx2 = (long long)stockPrices[i][0] - stockPrices[i - 1][0];

            if (dy1 * dx2 != dy2 * dx1)
                lines++;
        }

        return lines;
    }
};