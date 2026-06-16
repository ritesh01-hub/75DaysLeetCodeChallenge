class Solution {
public:
    int getSum(int a, int b) {
        // int sum = a+b;
        // return sum;
        while(b!=0){
            unsigned carry = (a&b)<<1;
            a ^=b;
            b = carry;
        }
        return a;
    }
};