class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int row = grid.size();
        int col = grid[0].size();

        int cc = 0;

        for(int r = 0; r < row; r++) {
            for(int c = 0; c < col; c++) {

                if(grid[r][c] == '0') continue;

                cc++;

                queue<pair<int,int>> qu;
                qu.push({r, c});

                grid[r][c] = '0';

                while(!qu.empty()) {

                    auto curr = qu.front();
                    qu.pop();

                    int currRow = curr.first;
                    int currCol = curr.second;

                    // up
                    if(currRow - 1 >= 0 &&
                       grid[currRow - 1][currCol] == '1') {

                        qu.push({currRow - 1, currCol});
                        grid[currRow - 1][currCol] = '0';
                    }

                    // down
                    if(currRow + 1 < row &&
                       grid[currRow + 1][currCol] == '1') {

                        qu.push({currRow + 1, currCol});
                        grid[currRow + 1][currCol] = '0';
                    }

                    // left
                    if(currCol - 1 >= 0 &&
                       grid[currRow][currCol - 1] == '1') {

                        qu.push({currRow, currCol - 1});
                        grid[currRow][currCol - 1] = '0';
                    }

                    // right
                    if(currCol + 1 < col &&
                       grid[currRow][currCol + 1] == '1') {

                        qu.push({currRow, currCol + 1});
                        grid[currRow][currCol + 1] = '0';
                    }
                }
            }
        }

        return cc;
    }
};