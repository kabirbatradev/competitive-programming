struct Node {
    int row;
    int col;
    int minutes; // aka distance
    Node(int row, int col, int minutes) : row(row), col(col), minutes(minutes) {}
};

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {

        int n = grid.size();
        int m = grid[0].size();

        // bfs from rotten oranges, identify any oranges that were never visited
        
        queue<Node> q;
        int freshCount = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // find rotten oranges and put into queue with 0 minutes aka distance
                if (grid[i][j] == 2) {
                    q.push(Node(i, j, 0));
                }
                if (grid[i][j] == 1) freshCount++;
            }
        }

        if (freshCount == 0) return 0; // can return early if no fresh oranges

        // for every node in q, go in 4 directions and add new nodes to q
            // node must be an orange
            // must be not visited
        
        // vector<vector<bool>> visited(n, vector<bool>(m, false));
        // can mark visited as -1 in the grid (instead of creating a new 2d array)

        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        int maxMinutes = 0;

        while (!q.empty()) {
            Node node = q.front();
            q.pop();

            int i = node.row;
            int j = node.col;

            // check if already visited (can have multiple references to same cell in q)
            if (grid[i][j] == -1) continue;

            // if previously fresh, then freshCount--;
            if (grid[i][j] == 1) freshCount--;

            // mark as visited and update max minutes
            grid[i][j] = -1;
            maxMinutes = max(maxMinutes, node.minutes);

            // consider all four directions for a new orange
            for (int k = 0; k < 4; k++) {
                int i2 = i + dx[k];
                int j2 = j + dy[k];

                // skip if out of bounds, or not orange (including visited)
                if (i2 < 0 || j2 < 0 || i2 >= n || j2 >= m || grid[i2][j2] != 1) {
                    continue;
                }

                // now we have an unvisited orange! push to q with +1 minutes
                q.push(Node(i2, j2, node.minutes+1));
            }
        
        }

        // special case: there is still an unvisited orange
        if (freshCount != 0) return -1;

        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < m; j++) {
        //         // find orange that is not visited
        //         if (grid[i][j] == 1 && !visited[i][j]) {
        //             return -1; // can return early
        //         }
        //     }
        // }

        return maxMinutes;
        
    }
};
