class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> numSet(nums.begin(), nums.end());
        int maxLen = 0;

        for (int num : numSet) {
            // Only start counting if 'num' is the START of a sequence
            if (numSet.find(num - 1) == numSet.end()) {
                int currNum = num;
                int currLen = 1;

                while (numSet.count(currNum + 1)) {
                    currNum++;
                    currLen++;
                }

                maxLen = max(maxLen, currLen);
            }
        }

        return maxLen;
    }
};