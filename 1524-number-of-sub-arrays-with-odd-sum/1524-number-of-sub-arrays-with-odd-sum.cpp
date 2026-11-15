class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {

        const int MOD = 1e9 + 7;

        long long even = 1;
        long long odd = 0;
        long long count = 0;

        int sum = 0;

        for(int num : arr) {

            sum += num;

            if(sum % 2 == 0) {
                count += odd;
                even++;
            }
            else {
                count += even;
                odd++;
            }

            count %= MOD;
        }

        return count;
    }
};