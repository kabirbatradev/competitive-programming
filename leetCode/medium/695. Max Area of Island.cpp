class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int bestSize = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    int size = dfs(i, j, grid, visited);
                    bestSize = max(size, bestSize);
                }
            }
        }

        return bestSize;
    }

    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};

    int dfs(int i, int j, vector<vector<int>>& grid, vector<vector<bool>>& visited) {
        if (visited[i][j]) return 0;
        visited[i][j] = true;

        int total = 1;

        for (int k = 0; k < 4; k++) {
            int i2 = i + dx[k];
            int j2 = j + dy[k];

            // check if out of bounds or if grid is 0 
            if (i2 < 0 || j2 < 0 || i2 >= grid.size() || j2 >= grid[0].size() || grid[i2][j2] == 0) {
                continue;
            }
            total += dfs(i2, j2, grid, visited);
        }

        return total;

    }
};