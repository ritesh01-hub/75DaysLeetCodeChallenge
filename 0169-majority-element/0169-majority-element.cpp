class Solution {
public:
    int majorityElement(vector<int>& nums) {
        // int n = nums.size();
        // sort(nums.begin(),nums.end());
        // return nums[n/2];
        // // int n = nums.size();
        // // for(int i =0;i<n;i++){
        // //     int count = 1;
        // //     for(int j = i+1;j<n;j++){
        // //         if(nums[i]==nums[j]) count++;

        // //     }
        // //     if(count>n/2) return nums[i];
        // // }
        // // return -1;

        int n = nums.size();
        unordered_map<int,int> mp;
        for(int x : nums){
            mp[x]++;
            if(mp[x]>n/2){
                return x;
            }
        }
        return -1;
    }
};