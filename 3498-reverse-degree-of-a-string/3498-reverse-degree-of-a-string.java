class Solution {
    public int reverseDegree(String s) {
        int ans = 0;

        for (int i = 0; i < s.length(); i++) {
            int reversePosition = 'z' - s.charAt(i) + 1;
            int stringPosition = i + 1;

            ans += reversePosition * stringPosition;
        }

        return ans;
    }
}