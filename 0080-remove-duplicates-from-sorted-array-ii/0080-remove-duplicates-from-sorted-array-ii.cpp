class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
      int idx = 0;

        for (int i = 0; i < nums.size(); i++) {

            if (idx < 2 || nums[i] != nums[idx - 2]) {
                nums[idx] = nums[i];
                idx++;
            }
        }

        return idx;   
    }
};