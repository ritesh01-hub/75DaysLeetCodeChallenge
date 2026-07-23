class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
         int n = nums.size();

        if (n <= 2)
            return n;

        int p = 0;

        while (n > 0) {
            p++;
            n >>= 1;
        }

        return 1 << p;
    }
};