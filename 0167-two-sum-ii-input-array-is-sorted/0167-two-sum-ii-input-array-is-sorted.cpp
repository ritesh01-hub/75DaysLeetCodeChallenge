class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {

        int  n = numbers.size();


        vector<int> ans;

        int i = 0;
        int j = n-1;

        while(i < j){
            int sum =  numbers[i] + numbers[j];

            if(sum == target) {
                return {i+1,j+1};

            }
            else if (sum > target){
                j--;
            }
            else{
                i++;
            }
        }

        // for(int i = 0;i<n;i++){
        //     for(int j = i+1;j<n;j++){
        //         if(numbers[i] + numbers[j] == target){
        //             return {i+1,j+1};
        //             // ans.push_back(i);
        //             // ans.push_back(j);
        //         }
        //     }
        // }

        

        return {-1,-1};
        
    }
};