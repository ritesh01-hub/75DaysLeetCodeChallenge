class Solution {

    static class Node {
        int[] cnt;    // Number of subarrays with each remainder
        int[] pref;   // Number of prefixes with each remainder
        int[] suff;   // Number of suffixes with each remainder
        int prod;     // Product of entire segment % k

        Node(int k) {
            cnt = new int[k];
            pref = new int[k];
            suff = new int[k];
        }
    }

    int n, k;
    Node[] tree;

    public int[] resultArray(int[] nums, int k, int[][] queries) {

        this.n = nums.length;
        this.k = k;

        tree = new Node[4 * n];

        build(1, 0, n - 1, nums);

        int[] ans = new int[queries.length];

        for (int q = 0; q < queries.length; q++) {

            int index = queries[q][0];
            int value = queries[q][1];
            int start = queries[q][2];
            int x = queries[q][3];

            // Update nums[index]
            update(1, 0, n - 1, index, value);

            // Query range [start ... n-1]
            Node res = query(1, 0, n - 1, start, n - 1);

            // IMPORTANT:
            // Remaining array must be a prefix of this range.
            ans[q] = res.pref[x];
        }

        return ans;
    }

    // --------------------------------------------------
    // BUILD
    // --------------------------------------------------

    void build(int node, int l, int r, int[] nums) {

        if (l == r) {
            tree[node] = makeNode(nums[l]);
            return;
        }

        int mid = l + (r - l) / 2;

        build(node * 2, l, mid, nums);
        build(node * 2 + 1, mid + 1, r, nums);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    // --------------------------------------------------
    // UPDATE
    // --------------------------------------------------

    void update(int node, int l, int r, int index, int value) {

        if (l == r) {
            tree[node] = makeNode(value);
            return;
        }

        int mid = l + (r - l) / 2;

        if (index <= mid) {
            update(node * 2, l, mid, index, value);
        } else {
            update(node * 2 + 1, mid + 1, r, index, value);
        }

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    // --------------------------------------------------
    // QUERY
    // --------------------------------------------------

    Node query(int node, int l, int r, int ql, int qr) {

        // Completely inside range
        if (ql <= l && r <= qr) {
            return tree[node];
        }

        int mid = l + (r - l) / 2;

        // Completely in left
        if (qr <= mid) {
            return query(node * 2, l, mid, ql, qr);
        }

        // Completely in right
        if (ql > mid) {
            return query(node * 2 + 1, mid + 1, r, ql, qr);
        }

        // Split between left and right
        Node left = query(node * 2, l, mid, ql, qr);
        Node right = query(node * 2 + 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }

    // --------------------------------------------------
    // LEAF NODE
    // --------------------------------------------------

    Node makeNode(int value) {

        Node res = new Node(k);

        int rem = value % k;

        res.prod = rem;

        // Only one element
        res.pref[rem] = 1;
        res.suff[rem] = 1;
        res.cnt[rem] = 1;

        return res;
    }

    // --------------------------------------------------
    // MERGE
    // --------------------------------------------------

    Node merge(Node left, Node right) {

        Node res = new Node(k);

        // Product of complete segment
        res.prod = (left.prod * right.prod) % k;

        // ==================================================
        // PREFIX
        // ==================================================

        // Prefix completely inside left
        for (int r = 0; r < k; r++) {
            res.pref[r] += left.pref[r];
        }

        // Prefix = entire left + prefix of right
        for (int r = 0; r < k; r++) {

            if (right.pref[r] == 0) {
                continue;
            }

            int newRem = (left.prod * r) % k;

            res.pref[newRem] += right.pref[r];
        }

        // ==================================================
        // SUFFIX
        // ==================================================

        // Suffix completely inside right
        for (int r = 0; r < k; r++) {
            res.suff[r] += right.suff[r];
        }

        // Suffix = suffix of left + entire right
        for (int r = 0; r < k; r++) {

            if (left.suff[r] == 0) {
                continue;
            }

            int newRem = (r * right.prod) % k;

            res.suff[newRem] += left.suff[r];
        }

        // ==================================================
        // ALL SUBARRAYS
        // ==================================================

        // Subarrays completely inside left/right
        for (int r = 0; r < k; r++) {

            res.cnt[r] += left.cnt[r];
            res.cnt[r] += right.cnt[r];
        }

        // Cross subarrays:
        // suffix of left + prefix of right
        for (int a = 0; a < k; a++) {

            if (left.suff[a] == 0) {
                continue;
            }

            for (int b = 0; b < k; b++) {

                if (right.pref[b] == 0) {
                    continue;
                }

                int newRem = (a * b) % k;

                res.cnt[newRem] +=
                        left.suff[a] * right.pref[b];
            }
        }

        return res;
    }
}