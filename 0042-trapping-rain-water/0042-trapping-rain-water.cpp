class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        // step 1 ; previous greatest element array:
         vector<int> prev(n);
       // int prev[n];
        prev[0] = -1;
        int max = height[0];
        for(int i = 1;i<n;i++){
            prev[i] = max;
            if(max<height[i]) max = height[i];
        }
        // step 2: next greatest element array:
         vector<int> next(n);
         //int next[n];

          next[n-1] = -1;
          max = height[n-1];
          for(int i =n-2;i>=0;i--){
            next[i] = max;
            if(max<height[i]) max = height[i];
          }

         // step 3: mninmum array:
           vector<int> mini(n);
        // int mini[n];  
         for(int i =0;i<n;i++){
            mini[i] = min(prev[i],next[i]);
         }

         //step 4:  calculating water:
         int water =0;
         for(int i =0;i<n-1;i++){
            if(height[i]<mini[i])
            water += (mini[i]-height[i]);
         }
    
         return water;
    }
    
};