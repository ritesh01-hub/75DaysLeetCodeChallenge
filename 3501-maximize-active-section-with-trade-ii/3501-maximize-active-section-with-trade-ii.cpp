class Solution {
    struct Group {
        int start;
        int len;
    };

    // Sparse Table for Range Maximum Query
    class SparseTable {
        vector<vector<int>> st;
        vector<int> lg;

    public:
        SparseTable(const vector<int>& a) {
            int n = a.size();

            lg.resize(n + 1);
            for (int i = 2; i <= n; i++)
                lg[i] = lg[i / 2] + 1;

            if (n == 0) return;

            int K = lg[n] + 1;
            st.assign(K, vector<int>(n));

            st[0] = a;

            for (int k = 1; k < K; k++) {
                for (int i = 0; i + (1 << k) <= n; i++) {
                    st[k][i] = max(
                        st[k - 1][i],
                        st[k - 1][i + (1 << (k - 1))]
                    );
                }
            }
        }

        int query(int l, int r) {
            if (l > r) return 0;

            int k = lg[r - l + 1];

            return max(
                st[k][l],
                st[k][r - (1 << k) + 1]
            );
        }
    };

public:
    vector<int> maxActiveSectionsAfterTrade(
        string s,
        vector<vector<int>>& queries
    ) {
        int n = s.size();

        // Total number of 1s in original string
        int ones = 0;
        for (char ch : s) {
            if (ch == '1')
                ones++;
        }

        // Store all zero groups
        vector<Group> zeroGroups;

        // zeroGroupIndex[i] =
        // latest zero-group index seen up to position i
        vector<int> zeroGroupIndex(n, -1);

        for (int i = 0; i < n; i++) {

            if (s[i] == '0') {

                if (i > 0 && s[i - 1] == '0') {
                    zeroGroups.back().len++;
                }
                else {
                    zeroGroups.push_back({i, 1});
                }
            }

            zeroGroupIndex[i] = (int)zeroGroups.size() - 1;
        }

        // No zeros => no improvement possible
        if (zeroGroups.empty()) {
            return vector<int>(queries.size(), ones);
        }

        /*
            merge[i] =
            length(zeroGroup[i]) + length(zeroGroup[i+1])

            Pattern:

            000 111 00

            If middle 111 is removed:

            000 000 00

            Then whole zero block can become 1.

            Gain = 3 + 2 = 5
        */
        vector<int> merge;

        for (int i = 0; i + 1 < (int)zeroGroups.size(); i++) {
            merge.push_back(
                zeroGroups[i].len +
                zeroGroups[i + 1].len
            );
        }

        SparseTable st(merge);

        vector<int> ans;

        for (auto& q : queries) {

            int l = q[0];
            int r = q[1];

            int left = -1;
            int right = -1;

            /*
                If l lies inside a zero-group,
                only the zero portion from l onward
                belongs to this query.
            */
            if (zeroGroupIndex[l] != -1) {
                int id = zeroGroupIndex[l];

                left =
                    zeroGroups[id].len -
                    (l - zeroGroups[id].start);
            }

            /*
                If r lies inside a zero-group,
                only the portion up to r belongs
                to this query.
            */
            if (zeroGroupIndex[r] != -1) {
                int id = zeroGroupIndex[r];

                right =
                    r - zeroGroups[id].start + 1;
            }

            int startGroup = zeroGroupIndex[l] + 1;

            int endGroup;

            if (s[r] == '1')
                endGroup = zeroGroupIndex[r];
            else
                endGroup = zeroGroupIndex[r] - 1;

            /*
                For adjacent zero groups:

                group 0 + group 1 -> merge[0]
                group 1 + group 2 -> merge[1]

                So if complete groups are
                [startGroup ... endGroup]

                merge indices:
                [startGroup ... endGroup-1]
            */

            int startMerge = startGroup;
            int endMerge = endGroup - 1;

            int best = ones;

            // Case 1:
            // Query starts and ends inside two
            // adjacent zero groups.
            if (
                s[l] == '0' &&
                s[r] == '0' &&
                zeroGroupIndex[l] + 1 == zeroGroupIndex[r]
            ) {
                best = max(
                    best,
                    ones + left + right
                );
            }

            // Case 2:
            // Completely covered internal zero groups
            else if (startMerge <= endMerge) {

                best = max(
                    best,
                    ones + st.query(startMerge, endMerge)
                );
            }

            // Case 3:
            // Left boundary zero-group is partial
            if (
                s[l] == '0' &&
                zeroGroupIndex[l] + 1 <= endGroup
            ) {
                best = max(
                    best,
                    ones +
                    left +
                    zeroGroups[zeroGroupIndex[l] + 1].len
                );
            }

            // Case 4:
            // Right boundary zero-group is partial
            if (
                s[r] == '0' &&
                zeroGroupIndex[l] <
                zeroGroupIndex[r] - 1
            ) {
                best = max(
                    best,
                    ones +
                    right +
                    zeroGroups[zeroGroupIndex[r] - 1].len
                );
            }

            ans.push_back(best);
        }

        return ans;
    }
};