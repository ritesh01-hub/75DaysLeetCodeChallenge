class Solution {
public:
    int findPeakElement(vector<int>& nums) {

        int n = nums.size();
        if(n == 1) return 0;
        int lo = 0;
        int hi = n-1;
        while(lo<hi){
            int mid = lo + (hi-lo)/2;
            if(nums[mid]>nums[mid+1]) hi = mid;
            
            else lo = mid+1;
        }
        
        return lo;
    }
};