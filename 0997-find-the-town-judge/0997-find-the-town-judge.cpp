class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
         vector<int> indegree(n + 1, 0);
        vector<int> outdegree(n + 1, 0);

        for(auto &t : trust) {
            int a = t[0];
            int b = t[1];

            outdegree[a]++; // a trusts someone
            indegree[b]++;  // b is trusted by someone
        }

        for(int i = 1; i <= n; i++) {
            // Judge trusts nobody and everyone trusts judge
            if(outdegree[i] == 0 && indegree[i] == n - 1) {
                return i;
            }
        }

        return -1;
    }
};