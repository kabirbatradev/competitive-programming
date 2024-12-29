class Solution {
public:
    int minimumOperations(vector<vector<int>>& grid) {

        // go down each column
        // push the number until its at least 1 bigger than the prev

        int ret = 0;

        // for every column
        for (int c = 0; c < grid[0].size(); c++) {

            // set to value in top row
            int prev = grid[0][c];
            
            for (int r = 1; r < grid.size(); r++) {
                if (grid[r][c] <= prev) {
                    ret += prev+1 - grid[r][c];
                    grid[r][c] = prev + 1;
                }
                prev = grid[r][c];
            }

        }

        return ret;
        
    }
};