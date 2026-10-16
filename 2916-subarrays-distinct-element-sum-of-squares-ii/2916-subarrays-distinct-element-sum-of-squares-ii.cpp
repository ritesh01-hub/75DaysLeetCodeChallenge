class Solution {
public:
    static const long long MOD = 1000000007;

    struct Node {
        long long sum = 0;     // sum of distinct counts
        long long sq = 0;      // sum of squares
        long long lazy = 0;    
    };

    vector<Node> tree;

    void apply(int node, int l, int r) {
        long long len = r - l + 1;

        // (x + 1)^2 = x^2 + 2x + 1
        tree[node].sq =
            (tree[node].sq + 2LL * tree[node].sum + len) % MOD;

        tree[node].sum =
            (tree[node].sum + len) % MOD;

        tree[node].lazy++;
    }

    void push(int node, int l, int r) {
        if (tree[node].lazy == 0 || l == r)
            return;

        int mid = l + (r - l) / 2;

        long long times = tree[node].lazy;

        // Applying +times at once
        long long leftLen = mid - l + 1;
        long long rightLen = r - mid;

        // For x -> x + times:
        // (x+t)^2 = x^2 + 2tx + t^2

        tree[node * 2].sq =
            (tree[node * 2].sq
             + 2LL * times * tree[node * 2].sum
             + times * times % MOD * leftLen) % MOD;

        tree[node * 2].sum =
            (tree[node * 2].sum + times * leftLen) % MOD;

        tree[node * 2].lazy += times;

        tree[node * 2 + 1].sq =
            (tree[node * 2 + 1].sq
             + 2LL * times * tree[node * 2 + 1].sum
             + times * times % MOD * rightLen) % MOD;

        tree[node * 2 + 1].sum =
            (tree[node * 2 + 1].sum + times * rightLen) % MOD;

        tree[node * 2 + 1].lazy += times;

        tree[node].lazy = 0;
    }

    void update(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return;

        if (ql <= l && r <= qr) {
            apply(node, l, r);
            return;
        }

        push(node, l, r);

        int mid = l + (r - l) / 2;

        update(node * 2, l, mid, ql, qr);
        update(node * 2 + 1, mid + 1, r, ql, qr);

        tree[node].sum =
            (tree[node * 2].sum + tree[node * 2 + 1].sum) % MOD;

        tree[node].sq =
            (tree[node * 2].sq + tree[node * 2 + 1].sq) % MOD;
    }

    int sumCounts(vector<int>& nums) {
        int n = nums.size();

        tree.resize(4 * n + 5);

        vector<int> last(100001, -1);

        long long ans = 0;

        for (int r = 0; r < n; r++) {

            int x = nums[r];

            int prev = last[x];

          
            update(1, 0, n - 1, prev + 1, r);

           
            ans = (ans + tree[1].sq) % MOD;

            last[x] = r;
        }

        return ans;
    }
};