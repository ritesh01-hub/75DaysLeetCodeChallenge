class Solution {

    public int totalNumbers(int[] digits) {

        int[] freq = new int[10];

       
        for (int d : digits) {
            freq[d]++;
        }

        int ans = 0;

       
        for (int last = 0; last <= 8; last += 2) {

            if (freq[last] == 0) continue;

            freq[last]--;

            for (int first = 1; first <= 9; first++) {

                if (freq[first] == 0) continue;

                freq[first]--;

              
                for (int middle = 0; middle <= 9; middle++) {
                    if (freq[middle] > 0) {
                        ans++;
                    }
                }

                freq[first]++;
            }

            freq[last]++;
        }

        return ans;
    }
}