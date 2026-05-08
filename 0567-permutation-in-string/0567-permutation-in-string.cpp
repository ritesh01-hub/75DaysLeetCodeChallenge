class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n1 = s1.size();
        int n2 = s2.size();

        if(n1 > n2) return false;

        vector<int> freq1(26, 0);
        vector<int> window(26, 0);

        // frequency of s1
        for(char ch : s1){
            freq1[ch - 'a']++;
        }

        int left = 0;

        for(int right = 0; right < n2; right++){

            // add current character to window
            window[s2[right] - 'a']++;

            // maintain window size = n1
            if(right - left + 1 > n1){
                window[s2[left] - 'a']--;
                left++;
                  }

            // compare frequencies
            if(window == freq1){
                return true;
            }
        }

        return false;
    }
};