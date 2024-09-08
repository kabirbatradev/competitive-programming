class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {

        vector<vector<bool>> visited(obstacleGrid.size(), vector<bool>(obstacleGrid[0].size(), 0));
        visited[0][0] = 1;
        return dfs(0,0, obstacleGrid, visited);
        
    }

    int dx[4] = {0,0,-1,1};
    int dy[4] = {-1,1,0,0};

    int dfs(int row, int col, vector<vector<int>>& grid, vector<vector<bool>>& visited) {

        if (row == grid.size()-1 && col == grid[0].size()-1) return 1;


        int sum =0;

        for (int i= 0; i < 4; i++) {
            int newRow = row + dx[i];
            int newCol = col + dy[i];

            // out of bounds
            if (newRow < 0 || newCol < 0 || newRow >= grid.size() || newCol >= grid[0].size()) {
                continue;
            }
            // obstacle
            if (grid[newRow][newCol] == 1) continue;
            // already visited in this path
            if (visited[newRow][newCol]) continue;

            // new path should have this tile visited
            visited[newRow][newCol] = 1;
            sum += dfs(newRow, newCol, grid, visited);
            visited[newRow][newCol] = 0;
            // remove from visited for other possible directions

        }
        
        return sum;
    }

    
};