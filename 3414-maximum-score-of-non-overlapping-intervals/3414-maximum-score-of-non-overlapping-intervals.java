class Solution {

    static class Interval {
        int l, r, w, idx;

        Interval(int l, int r, int w, int idx) {
            this.l = l;
            this.r = r;
            this.w = w;
            this.idx = idx;
        }
    }

    static class State {
        long score;
        List<Integer> indices;

        State(long score, List<Integer> indices) {
            this.score = score;
            this.indices = indices;
        }
    }

    public int[] maximumWeight(List<List<Integer>> intervals) {

        int n = intervals.size();

        Interval[] arr = new Interval[n];

        for (int i = 0; i < n; i++) {
            arr[i] = new Interval(
                intervals.get(i).get(0),
                intervals.get(i).get(1),
                intervals.get(i).get(2),
                i
            );
        }

       
        Arrays.sort(arr, (a, b) -> {
            if (a.r != b.r)
                return Integer.compare(a.r, b.r);

            return Integer.compare(a.l, b.l);
        });

       
        int[] rights = new int[n];

        for (int i = 0; i < n; i++) {
            rights[i] = arr[i].r;
        }

        
        int[] prev = new int[n];

        for (int i = 0; i < n; i++) {
            prev[i] = lowerBound(rights, arr[i].l);
        }

        
        State[][] dp = new State[n + 1][5];

        for (int k = 0; k <= 4; k++) {
            dp[0][k] = new State(0, new ArrayList<>());
        }

        for (int i = 1; i <= n; i++) {

            Interval cur = arr[i - 1];

            for (int k = 0; k <= 4; k++) {

               
                State notTake = dp[i - 1][k];

                State best = notTake;

               
                if (k > 0) {

                    State before = dp[prev[i - 1]][k - 1];

                    long newScore = before.score + cur.w;

                    List<Integer> newIndices =
                        new ArrayList<>(before.indices);

                    newIndices.add(cur.idx);

                    Collections.sort(newIndices);

                    State take = new State(newScore, newIndices);

                    if (better(take, best)) {
                        best = take;
                    }
                }

                dp[i][k] = best;
            }
        }

        return dp[n][4].indices.stream()
                .mapToInt(Integer::intValue)
                .toArray();
    }

   
    static int lowerBound(int[] arr, int target) {

        int lo = 0;
        int hi = arr.length;

        while (lo < hi) {

            int mid = lo + (hi - lo) / 2;

            if (arr[mid] < target) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }

        return lo;
    }

    static boolean better(State a, State b) {

        if (a.score != b.score) {
            return a.score > b.score;
        }

        int n = Math.min(a.indices.size(), b.indices.size());

        for (int i = 0; i < n; i++) {

            if (!a.indices.get(i).equals(b.indices.get(i))) {
                return a.indices.get(i) < b.indices.get(i);
            }
        }

        return a.indices.size() < b.indices.size();
    }
}