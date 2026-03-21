class Solution {
public:
    void moveZeroes(vector<int>& nums) {

        // sort(nums.begin(), nums.end());
        // reverse(nums.begin(),nums.end());
    
        // bubble sort 
        int n = nums.size();
        for(int i = 0;i<n-1;i++){
            for(int j =0;j<n-1-i;j++){
                if(nums[j]==0){
                    swap(nums[j],nums[j+1]);

                }
            }
        }
        
    }
};