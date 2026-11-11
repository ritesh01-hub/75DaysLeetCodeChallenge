
class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {

        long long common = min(need1, need2);

        // Option 1: Use common items for overlapping needs
        long long costA = common * 1LL * costBoth
                        + (need1 - common) * 1LL * cost1
                        + (need2 - common) * 1LL * cost2;

        // Option 2: Buy everything separately
        long long costB = need1 * 1LL * cost1
                        + need2 * 1LL * cost2;

        // Option 3: Buy common items for all requirements
        long long costC = max(need1, need2) * 1LL * costBoth;

        return min({costA, costB, costC});
    }
};
