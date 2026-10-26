class Solution {
public:
    int m, n;
    
    long long dfs(int r, int c, vector<vector<int>>& grid) {
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 0) {
            return 0;
        }

        long long sum = grid[r][c];
        
        // Mark as visited
        grid[r][c] = 0;

        sum += dfs(r + 1, c, grid);
        sum += dfs(r - 1, c, grid);
        sum += dfs(r, c + 1, grid);
        sum += dfs(r, c - 1, grid);

        return sum;
    }

    int countIslands(vector<vector<int>>& grid, int k) {
        m = grid.size();
        n = grid[0].size();

        int ans = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (grid[i][j] > 0) {
                    long long sum = dfs(i, j, grid);

                    if (sum % k == 0) {
                        ans++;
                    }
                }
            }
        }

        return ans;
    }
};