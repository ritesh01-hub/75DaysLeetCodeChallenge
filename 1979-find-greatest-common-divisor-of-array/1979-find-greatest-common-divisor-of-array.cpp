class Solution {
public:
    int gcd(int a, int b){
        for(int i = min(a,b);i>=2;i--){
            if(a%i==0 && b%i==0) return i;
        }
        return 1;
    }
    int findGCD(vector<int>& nums) {
    int mx = *max_element(nums.begin(),nums.end());
    int mn = *min_element(nums.begin(),nums.end());
    return gcd(mx,mn);
    }
};