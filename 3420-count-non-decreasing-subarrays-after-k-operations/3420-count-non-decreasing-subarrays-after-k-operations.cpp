
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int LOG = 18;

        vector<long long> pref(n + 1, 0);

        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + nums[i];
        }

        // Step 1: Find next greater element
        vector<int> nxt(n, n);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                st.pop();
            }

            if (!st.empty()) {
                nxt[i] = st.top();
            }

            st.push(i);
        }

        // Step 2: Binary lifting
        vector<vector<int>> jump(LOG, vector<int>(n + 1, n));
        vector<vector<long long>> cost(
            LOG, vector<long long>(n + 1, 0)
        );

        for (int i = 0; i < n; i++) {
            int j = nxt[i];

            jump[0][i] = j;

            cost[0][i] =
                1LL * nums[i] * (j - i)
                - (pref[j] - pref[i]);
        }

        for (int p = 1; p < LOG; p++) {
            for (int i = 0; i < n; i++) {
                int mid = jump[p - 1][i];

                jump[p][i] = jump[p - 1][mid];

                cost[p][i] =
                    cost[p - 1][i] + cost[p - 1][mid];
            }
        }

        // Step 3: Calculate operations for [l, r]
        auto getCost = [&](int l, int r) -> long long {
            long long total = 0;
            int pos = l;

            for (int p = LOG - 1; p >= 0; p--) {
                int next = jump[p][pos];

                if (next <= r) {
                    total += cost[p][pos];
                    pos = next;
                }
            }

            total += 1LL * nums[pos] * (r - pos + 1)
                     - (pref[r + 1] - pref[pos]);

            return total;
        };

        // Step 4: Binary search for each right endpoint
        long long ans = 0;

        for (int r = 0; r < n; r++) {
            int low = 0, high = r;
            int left = r;

            while (low <= high) {
                int mid = low + (high - low) / 2;

                if (getCost(mid, r) <= k) {
                    left = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }

            ans += (r - left + 1);
        }

        return ans;
    }
};
