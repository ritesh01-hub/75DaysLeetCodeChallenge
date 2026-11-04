class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        multiset<int> left, right;
        long long sumLeft = 0, sumRight = 0;

        int target = (x + 1) / 2;

        // Insert an element (FIXED: compare with right's min)
        auto add = [&](int val) {
            if (right.empty() || val <= *right.begin()) {
                left.insert(val);
                sumLeft += val;
            } else {
                right.insert(val);
                sumRight += val;
            }
        };

        // Remove an element
        auto remove = [&](int val) {
            auto it = left.find(val);

            if (it != left.end()) {
                left.erase(it);
                sumLeft -= val;
            } else {
                it = right.find(val);
                right.erase(it);
                sumRight -= val;
            }
        };

        // Balance both multisets
        auto balance = [&]() {
            while ((int)left.size() > target) {
                int val = *left.rbegin();

                left.erase(prev(left.end()));
                sumLeft -= val;

                right.insert(val);
                sumRight += val;
            }

            while ((int)left.size() < target) {
                int val = *right.begin();

                right.erase(right.begin());
                sumRight -= val;

                left.insert(val);
                sumLeft += val;
            }
        };

        // Calculate minimum operations for current window
        auto getCost = [&]() -> long long {
            long long median = *left.rbegin();

            long long leftSize = (long long)left.size();
            long long rightSize = (long long)right.size();

            return median * leftSize - sumLeft
                 + sumRight - median * rightSize;
        };

        // Store cost of every window of size x
        vector<long long> cost(n - x + 1);

        // First window
        for (int i = 0; i < x; i++) {
            add(nums[i]);
        }

        balance();
        cost[0] = getCost();

        // Sliding window
        for (int i = x; i < n; i++) {
            remove(nums[i - x]);
            add(nums[i]);

            balance();

            cost[i - x + 1] = getCost();
        }

        // Dynamic Programming
        const long long INF = 1e18;

        vector<long long> prev(n + 1, 0);
        vector<long long> curr(n + 1, INF);

        for (int t = 1; t <= k; t++) {
            fill(curr.begin(), curr.end(), INF);

            for (int i = 1; i <= n; i++) {

                // Option 1: Skip current element
                curr[i] = curr[i - 1];

                // Option 2: Select a subarray of size x
                if (i >= x && prev[i - x] != INF) {
                    curr[i] = min(
                        curr[i],
                        prev[i - x] + cost[i - x]
                    );
                }
            }

            prev.swap(curr);
        }

        return prev[n];
    }
};