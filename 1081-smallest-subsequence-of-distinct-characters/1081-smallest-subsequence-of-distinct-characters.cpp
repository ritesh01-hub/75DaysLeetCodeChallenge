class Solution {
public:
    string smallestSubsequence(string s) {

        // Last occurrence of each character
        vector<int> lastIndex(26);

        for (int i = 0; i < s.length(); i++) {
            lastIndex[s[i] - 'a'] = i;
        }

        // Check whether a character is already in answer
        vector<bool> visited(26, false);

        string ans;

        for (int i = 0; i < s.length(); i++) {

            char ch = s[i];

            // Skip if already included
            if (visited[ch - 'a'])
                continue;

            // Remove larger characters if they appear later again
            while (!ans.empty() &&
                   ans.back() > ch &&
                   lastIndex[ans.back() - 'a'] > i) {

                visited[ans.back() - 'a'] = false;
                ans.pop_back();
            }

            ans.push_back(ch);
            visited[ch - 'a'] = true;
        }

        return ans;
    }
};