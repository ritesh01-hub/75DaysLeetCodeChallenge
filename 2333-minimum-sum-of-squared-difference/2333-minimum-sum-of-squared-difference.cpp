class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2,
                               int k1, int k2) {
        int n = nums1.size();
        long long k = (long long)k1 + k2;

        vector<int> diff(n);
        int maxi = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            maxi = max(maxi, diff[i]);
        }

        long long total = 0;
        for (int d : diff) {
            total += d;
        }

        // If all differences can be eliminated
        if (total <= k) return 0;

        int left = 0, right = maxi;

        // Find the smallest maximum difference possible
        while (left < right) {
            int mid = left + (right - left) / 2;
            long long operations = 0;

            for (int d : diff) {
                if (d > mid) {
                    operations += d - mid;
                }
            }

            if (operations <= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        int limit = left;
        long long ans = 0;
        long long remaining = k;

        for (int d : diff) {
            if (d > limit) {
                remaining -= d - limit;
                d = limit;
            }
            ans += 1LL * d * d;
        }

        // Use remaining operations to reduce differences from limit to limit-1
        for (int d : diff) {
            if (remaining > 0 && d >= limit) {
                // This element can be reduced by one more
                ans -= 2LL * limit - 1;
                remaining--;
            }
        }

        return ans;
    }
};