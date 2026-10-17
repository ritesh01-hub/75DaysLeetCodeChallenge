class Solution {
public:

    int digitSum(int x) {
        int sum = 0;

        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }

        return sum;
    }

    int minSwaps(vector<int>& nums) {

        int n = nums.size();

        // Store {digitSum, value}
        vector<pair<int, int>> v;

        for (int x : nums) {
            v.push_back({digitSum(x), x});
        }

        // Sorted according to digit sum,
        // and if equal, according to value
        sort(v.begin(), v.end());

        // target[i] = value that should be at index i
        vector<int> target;

        for (auto &p : v) {
            target.push_back(p.second);
        }

        // value -> current index
        unordered_map<int, int> pos;

        for (int i = 0; i < n; i++) {
            pos[nums[i]] = i;
        }

        int swaps = 0;

        for (int i = 0; i < n; i++) {

            // Already correct
            if (nums[i] == target[i])
                continue;

            // Find where target[i] currently is
            int j = pos[target[i]];

            // Swap
            swap(nums[i], nums[j]);

            // Update positions
            pos[nums[j]] = j;
            pos[nums[i]] = i;

            swaps++;
        }

        return swaps;
    }
};