class Solution {
    public int maxSubArray(int[] nums) {
        int n = nums.length;


        int currSum = nums[0];
        int maxSum = nums[0];

        for(int i = 1;i<n;i++){

            currSum = Math.max(nums[i] , currSum + nums[i]);

            maxSum = Math.max(maxSum , currSum);
            // currSum += nums[i];
            // if(maxSum  < currSum){
            //     maxSum = currSum;
            // }
            // if(currSum <0) currSum = 0;
          
        }
        return maxSum;
    }
}