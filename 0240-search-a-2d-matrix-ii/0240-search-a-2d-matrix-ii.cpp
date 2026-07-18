class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = matrix.size();
        int cols= matrix[0].size();
        /// Method : 1:
        // for(int i=0;i<row;i++){
        //     for(int j=0;j<cols;j++){
        //         if(matrix[i][j]==target ) return true;
        //     }
            
        // }
        // return false;
        
        // Method: 2: Binary search

        int i =0;
        int j = cols-1;
        while(i<=row-1&&j>=0){
            if(matrix[i][j]==target) return true;
            else if(matrix[i][j]> target ) j--;
            else i++;
        }
        return false;





    }
};