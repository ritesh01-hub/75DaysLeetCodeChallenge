class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.size();
        vector<pair<char,int>> runs;
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && s[j] == s[i]) j++;
            runs.push_back({s[i], j - i});
            i = j;
        } 
        int totalOnes = 0;
        for (char c : s) if (c == '1') totalOnes++;

        int bestGain = 0;
        for (int idx = 1; idx + 1 < (int)runs.size(); idx++) {
            if (runs[idx].first == '1') {
                int gain = runs[idx - 1].second + runs[idx + 1].second;
                bestGain = max(bestGain, gain);
            }
        }

        return totalOnes + bestGain;
    }
};