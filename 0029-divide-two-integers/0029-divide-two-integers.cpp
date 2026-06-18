class Solution {
public:
    int divide(int dividend, int divisor) {

        // Overflow case
        if (dividend == INT_MIN && divisor == -1)
            return INT_MAX;

        long long dvd = abs((long long)dividend);
        long long dvs = abs((long long)divisor);

        long long quotient = 0;

        while (dvd >= dvs) {

            long long temp = dvs;
            long long multiple = 1;

            while ((temp << 1) <= dvd) {
                temp <<= 1;
                multiple <<= 1;
            }

            dvd -= temp;
            quotient += multiple;
        }

        // Determine sign
        if ((dividend < 0) ^ (divisor < 0))
            quotient = -quotient;

        return (int)quotient;
    }
};