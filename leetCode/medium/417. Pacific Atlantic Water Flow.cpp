class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        
        // initialize reach grids
        vector<vector<bool>> reachPacific;
        vector<vector<bool>> reachAtlantic;
        for (int r = 0; r < heights.size(); r++) {
            reachPacific.push_back({});
            reachAtlantic.push_back({});
            for (int c = 0; c < heights[0].size(); c++) {
                reachPacific[r].push_back(0);
                reachAtlantic[r].push_back(0);
            }
        }

        for (int r = 0; r < heights.size(); r++) {
            backwardRain(r, 0, heights, reachPacific);
            backwardRain(r, heights[0].size()-1, heights, reachAtlantic);
        }

        for (int c = 0; c < heights[0].size(); c++) {
            backwardRain(0, c, heights, reachPacific);
            backwardRain(heights.size()-1, c, heights, reachAtlantic);
        }

        // check reach grids
        vector<vector<int>> ret;
        for (int r = 0; r < heights.size(); r++) {
            for (int c = 0; c < heights[0].size(); c++) {
                if (reachPacific[r][c] && reachAtlantic[r][c])
                    ret.push_back({r, c});
            }
        }

        return ret;
    }

    // up down left right
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {1, -1, 0, 0};
    
    void backwardRain(int row, int col, 
        vector<vector<int>>& heights, vector<vector<bool>>& reachGrid) {
        reachGrid[row][col] = true;

        for (int i=0; i < 4; i++) {
            int newR = row + dy[i];
            int newC = col + dx[i];

            if (
                newR >= 0 && newC >= 0
                && newR < heights.size() && newC < heights[0].size()
                && reachGrid[newR][newC] == false
                && heights[row][col] <= heights[newR][newC]
            ) {
                // unexplored and in bounds and going higher (backward rain)
                backwardRain(newR, newC, heights, reachGrid);
            }
        }
    }
};