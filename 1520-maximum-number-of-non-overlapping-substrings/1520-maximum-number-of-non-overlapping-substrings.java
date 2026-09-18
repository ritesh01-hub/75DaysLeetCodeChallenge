import java.util.*;

class Solution {
    public List<String> maxNumOfSubstrings(String s) {

        List<String> ans = new ArrayList<>();

        int n = s.length();

        
        int[] first = new int[26];
        int[] last = new int[26];

        Arrays.fill(first, n);
        Arrays.fill(last, -1);

       
        for (int i = 0; i < n; i++) {
            int ch = s.charAt(i) - 'a';

            first[ch] = Math.min(first[ch], i);
            last[ch] = i;
        }

       
        List<int[]> intervals = new ArrayList<>();

       
        for (int c = 0; c < 26; c++) {

            if (last[c] == -1) {
                continue;
            }

            int start = first[c];
            int end = last[c];

            boolean valid = true;

            for (int i = start; i <= end; i++) {

                int ch = s.charAt(i) - 'a';

                if (first[ch] < start) {
                    valid = false;
                    break;
                }

               
                end = Math.max(end, last[ch]);
            }

            if (valid) {
                intervals.add(new int[]{start, end});
            }
        }

       
        intervals.sort((a, b) -> {
            if (a[1] != b[1]) {
                return Integer.compare(a[1], b[1]);
            }
            return Integer.compare(a[0], b[0]);
        });

        int prevEnd = -1;

        for (int[] interval : intervals) {

            int start = interval[0];
            int end = interval[1];

            if (start > prevEnd) {
                ans.add(s.substring(start, end + 1));
                prevEnd = end;
            }
        }

        return ans;
    }
}