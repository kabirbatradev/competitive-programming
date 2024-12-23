class Solution {
public:
    void islandsAndTreasure(vector<vector<int>>& grid) {

        // identify all treasure chests, put neighbors into bfs queue
        // run bfs

        int n = grid.size();
        int m = grid[0].size();

        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        queue<pair<int,int>> q;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 0) {

                    for (int k = 0; k < 4; k++) {
                        int i2 = i + dx[k];
                        int j2 = j + dy[k];
                        
                        // neighbor: out of bounds or treasure
                        if (i2 < 0 || j2 < 0 || i2 >= n || j2 >= m || grid[i2][j2] == -1 || grid[i2][j2] == 0) {
                            continue;
                        }
                        q.push(make_pair(i2, j2));
                        grid[i2][j2] = 1; // label coord now
                    }

                }
            }
        }
        
        // coords are already labeled; just add neighbors to queue (and label them)
        while (!q.empty()) {
            pair<int, int> coord = q.front();
            q.pop();

            int label = grid[coord.first][coord.second];

            for (int k = 0; k < 4; k++) {
                int i2 = coord.first + dx[k];
                int j2 = coord.second + dy[k];
                
                // neighbor: out of bounds or treasure
                if (i2 < 0 || j2 < 0 || i2 >= n || j2 >= m || grid[i2][j2] == -1 || grid[i2][j2] == 0) {
                    continue;
                }
                // already labeled
                if (grid[i2][j2] <= label) {
                    continue;
                }
                q.push(make_pair(i2, j2));
                grid[i2][j2] = label+1; // label coord now
            }

        }

    }
};
