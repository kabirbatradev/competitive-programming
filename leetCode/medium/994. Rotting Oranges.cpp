struct Node {
    int row;
    int col;
    int minutes; // aka distance
    Node(int row, int col, int minutes) : row(row), col(col), minutes(minutes) {}
};

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {

        // bfs from rotten oranges, identify any oranges that were never visited
        
        int n = grid.size();
        int m = grid[0].size();
        
        // min heap to process closer nodes first 
        auto compare = [](Node a, Node b) { // this also works?
        // auto compare = [](const Node& a, const Node& b) {
            return a.minutes > b.minutes; // use "greater" for min heap;
        };
        priority_queue<Node, vector<Node>, decltype(compare)> pq(compare);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // find rotten oranges and put into priority queue with 0
                if (grid[i][j] == 2) {
                    pq.push(Node(i, j, 0));
                }
            }
        }

        // for every node in pq, go in 4 directions and add new nodes to pq
            // node must be an orange
            // must be not visited
        
        vector<vector<bool>> visited(n, vector<bool>(m, false));

        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        int maxMinutes = 0;

        while (!pq.empty()) {
            Node node = pq.top();
            pq.pop();

            int i = node.row;
            int j = node.col;

            // check if already visited (can have multiple references to same cell in pq)
            if (visited[i][j]) continue;

            // new orange! mark as visited and update max minutes
            visited[i][j] = true;
            maxMinutes = max(maxMinutes, node.minutes);

            // consider all four directions for a new orange
            for (int k = 0; k < 4; k++) {
                int i2 = i + dx[k];
                int j2 = j + dy[k];

                // skip if out of bounds, not orange, or already visited
                if (i2 < 0 || j2 < 0 || i2 >= n || j2 >= m || grid[i2][j2] != 1 || visited[i2][j2]) {
                    continue;
                }

                // now we have an unvisited orange! push to pq with +1 minutes
                pq.push(Node(i2, j2, node.minutes+1));
            }
        
        }

        // special case: there is still an unvisited orange
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // find orange that is not visited
                if (grid[i][j] == 1 && !visited[i][j]) {
                    return -1; // can return early
                }
            }
        }

        return maxMinutes;
        
    }
};





/*
class Solution {
public:
    int n,m;
    int orangesRotting(vector<vector<int>>& grid) {

        // what is the farthest distance an orange is from rotten orange?

        // at orange position, can state distance from rotten orange (to use for future orange)

        // basically dfs from every orange, using already visited oranges values directly

        n = grid.size();
        m = grid[0].size();

        vector<vector<int>> minutes(n, vector<int>(m, -1));

        int maxMinutes = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // if orange and not already visited (visited means -1)
                if (grid[i][j] == 1 && minutes[i][j] != -1) {
                    int minutesTaken = dfs(i, j, grid, minutes);

                    // special case: orange never gets rotten (still -1)
                    if (minutesTaken == -1) return -1;
                    maxMinutes = max(maxMinutes, minutesTaken);
                    
                }
            }
        }

        return maxMinutes;
        
    }

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    int dfs(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& minutes) {

        // if at rotten orange, minutes taken is 0 automatically
        if (grid[i][j] == 2) return 0;

        // if already visited (minutes is not -1, then return that cached value)
        if (minutes[i][j] != -1) return minutes[i][j];
        
        // check all four directions
        for (int k = 0; k < 4; k++) {
            int i2 = i + dx[k];
            int j2 = j + dy[k];

            // skip if out of bounds, if empty (grid = 0)
            if (i2 < 0 || j2 < 0 || i2 >= n || j2 >= m || grid[i2][j2] == 0) {
                continue;
            }
            int minutesTaken = dfs(i2, j2, grid, minutes);

        }
    }
};
*/