class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        
         int n = nums.size();
        
        // Step 1: initial window sum
        int windowSum = 0;
        for(int i = 0; i < k; i++) {
            windowSum += nums[i];
        }
        
        int maxSum = windowSum;
        
        // Step 2: slide the window
        for(int i = k; i < n; i++) {
            windowSum += nums[i];      // add next
            windowSum -= nums[i - k];  // remove old
            
            maxSum = max(maxSum, windowSum);
        }
        
        return (double)maxSum / k;
    }
};