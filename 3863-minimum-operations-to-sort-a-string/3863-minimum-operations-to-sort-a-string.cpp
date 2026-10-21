class Solution {
public:
    int minOperations(string s) {
        int n = s.size();

        // Already sorted
        if (is_sorted(s.begin(), s.end())) {
            return 0;
        }

        // Only single-character substrings can be sorted
        if (n == 2) {
            return -1;
        }

        char mn = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());

        // One operation is enough
        if (s[0] == mn || s[n - 1] == mx) {
            return 1;
        }

        // If min or max is somewhere in the middle,
        // two operations are enough.
        for (int i = 1; i < n - 1; i++) {
            if (s[i] == mn || s[i] == mx) {
                return 2;
            }
        }

        // Here, max is at the beginning
        // and min is at the end.
        return 3;
    }
};