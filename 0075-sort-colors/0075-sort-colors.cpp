class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
         int nozeros = 0;
        int noones =0; 
        int notwo = 0;
        for(int i =0;i<n;i++){
            if(nums[i]==0) nozeros++;
            else if(nums[i] ==1) noones++;
            else notwo++;

        }
        /// filling 
        for(int i =0;i<n;i++){
            if(i<nozeros) nums[i]=0;
            else if(i<(nozeros+noones)) nums[i]=1;
            else nums[i]= 2;

        }
        return ;
    }
};