class Solution {
public:
    using ll = long long;

    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();

        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());

        const ll BASE = 1000003LL;
        const ll MOD = 1000000007LL;

        // prefix hash + powers
        vector<ll> powBase(n + 1);
        vector<ll> prefNums(n + 1);
        vector<ll> prefSorted(n + 1);

        powBase[0] = 1;

        for (int i = 0; i < n; i++) {
            powBase[i + 1] = (powBase[i] * BASE) % MOD;

            prefNums[i + 1] =
                (prefNums[i] * BASE + nums[i]) % MOD;

            prefSorted[i + 1] =
                (prefSorted[i] * BASE + sorted[i]) % MOD;
        }

        auto getHash = [&](vector<ll>& pref, int l, int r) -> ll {
            // [l, r)
            return (pref[r] -
                    pref[l] * powBase[r - l] % MOD +
                    MOD) % MOD;
        };

        auto isRotation = [&](int l, int r) -> bool {
            int len = r - l;

            // Original block
            ll target = getHash(prefNums, l, r);


            for (int shift = 0; shift < len; shift++) {

                ll h1 = getHash(
                    prefSorted,
                    l + shift,
                    r
                );

                ll h2 = getHash(
                    prefSorted,
                    l,
                    l + shift
                );

               

                ll combined =
                    (h1 * powBase[shift] + h2) % MOD;

                if (combined == target)
                    return true;
            }

            return false;
        };

        long long ans = 0;

        // k must divide n
        for (int k = 1; k <= n; k++) {

            if (n % k != 0)
                continue;

            bool possible = true;

            for (int l = 0; l < n; l += k) {

                int r = l + k;

                if (!isRotation(l, r)) {
                    possible = false;
                    break;
                }
            }

            if (possible)
                ans += k;
        }

        return (int)ans;
    }
};