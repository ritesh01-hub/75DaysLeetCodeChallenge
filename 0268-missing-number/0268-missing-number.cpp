class Solution {
public:
    int missingNumber(vector<int>& nums){
        int n = nums.size();
        int total = n*(n+1)/2;
        int sumAr = 0;
        for(int i =0;i<n;i++){
            sumAr+=nums[i];
        }
        int missing = total-sumAr;
        return missing;

        
       

    // int n = nums.size();
    // int xOr = 0;
    // for(int i =0;i<=n;i++){
    //     xOr ^= i;
    // }
    // for(int x: nums){
    //     xOr ^= x;
    // }
    // return xOr;

        
     }
};