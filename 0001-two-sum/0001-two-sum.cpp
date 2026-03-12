class Solution {
public:
    vector<int> twoSum(vector<int>& arr, int target) {
        /// initiallised vector to stored index
        vector<int> ans(2);
        int n = arr.size();
        for(int i =0;i<n;i++){
            
            for(int j = i+1;j<n;j++){
                if(arr[i]+arr[j]==target){
                   
                    ans[0]= i;
                    ans[1]= j;
                    return ans;
                }
            }     
        }
        return ans;   
    }
};