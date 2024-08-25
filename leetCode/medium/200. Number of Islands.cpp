class Solution {
public:

    vector<vector<bool>> visited;

    int numIslands(vector<vector<char>>& grid) {

        for (int i = 0; i < grid.size(); i++) {
            visited.push_back({});
            for (int j = 0; j < grid[0].size(); j++) {
                visited[i].push_back(false);
            }
        }

        int count = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                // only not visited land survive this check
                if (visited[i][j] || grid[i][j] == '0') continue;

                // cout << "new island at " << i << " " << j << endl;

                // start visiting the new island, increase count by 1
                count++;
                dfs(i, j, grid);
            }
        }

        // for (int i = 0; i < grid.size(); i++) {
        //     for (int j = 0; j < grid[0].size(); j++) {
        //         cout << visited[i][j] << " ";
        //     }
        //     cout << endl;
        // }


        return count;
        
    }

    int dx[4] = {0,0,-1,1};
    int dy[4] = {-1,1, 0, 0};

    void dfs(int i, int j, vector<vector<char>>& grid) {
        // if out of bounds, if water, if visited
        if (i < 0 
            || j < 0 
            || i >= grid.size() 
            || j >= grid[0].size() 
            || grid[i][j] == '0' 
            || visited[i][j]
        ) {
            return;
        }

        // yes i got '0' and 0 confused :c
        // if (grid[i][j] == 0) {
        //     cout << "what" << endl;
        // }
        
        // now visited
        // printf("marking i %d, j %d as visited\n", i, j);
        // cout << "grid = " << grid[i][j] << endl;
        visited[i][j] = true;

        // go in 4 directions
        for (int k = 0; k < 4; k++) {
            int newi = i+ dx[k];
            int newj = j+dy[k];

            dfs(newi, newj, grid);
        }

    }
};