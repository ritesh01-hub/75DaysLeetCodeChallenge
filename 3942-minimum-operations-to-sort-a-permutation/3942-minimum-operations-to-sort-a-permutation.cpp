class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int ans = INT_MAX;

        // Check whether nums itself can become sorted
        // using rotations.
        int pos = find(nums.begin(), nums.end(), 0) - nums.begin();

        bool ok = true;

        for (int i = 0; i < n; i++) {
            if (nums[(pos + i) % n] != i) {
                ok = false;
                break;
            }
        }

        if (ok) {
           
            ans = min(pos, n - pos + 2);
        }

        // Check reverse(nums)
        vector<int> rev = nums;
        reverse(rev.begin(), rev.end());

        int rpos = find(rev.begin(), rev.end(), 0) - rev.begin();

        ok = true;

        for (int i = 0; i < n; i++) {
            if (rev[(rpos + i) % n] != i) {
                ok = false;
                break;
            }
        }

        if (ok) {
            // One reverse + rotations
            ans = min(ans, 1 + min(rpos, n - rpos));
        }

        return ans == INT_MAX ? -1 : ans;
    }
};