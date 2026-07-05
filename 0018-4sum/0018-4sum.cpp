class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<vector<int>> ans;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 3; i++) {

            // Skip duplicate i
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            for (int j = i + 1; j < n - 2; j++) {

                // Skip duplicate j
                if (j > i + 1 && nums[j] == nums[j - 1])
                    continue;

                int p = j + 1;
                int q = n - 1;

                while (p < q) {

                    long long sum = (long long)nums[i] +
                                    (long long)nums[j] +
                                    (long long)nums[p] +
                                    (long long)nums[q];

                    if (sum < target) {
                        p++;
                    }
                    else if (sum > target) {
                        q--;
                    }
                    else {

                        ans.push_back({nums[i], nums[j], nums[p], nums[q]});

                        p++;
                        q--;

                        // Skip duplicate p
                        while (p < q && nums[p] == nums[p - 1])
                            p++;

                        // Skip duplicate q
                        while (p < q && nums[q] == nums[q + 1])
                            q--;
                    }
                }
            }
        }

        return ans;
    }
};