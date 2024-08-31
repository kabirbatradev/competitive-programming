class Solution {
public:
    /**
     * @param maze: the maze
     * @param start: the start
     * @param destination: the destination
     * @return: whether the ball could stop at the destination
     */
    bool hasPath(vector<vector<int>> &maze, vector<int> &start, vector<int> &destination) {
        
        // dfs: try rolling ball in all 4 directions (backward is not required)
        // mark new cells where the ball stopped as visited
        // potential optimization: mark cells along the way (+direction information) with the cell you will end up
            // so that you don't need to simulate rolling the ball all the way down every time you take that path

        vector<vector<bool>> visited;
        for (int i = 0; i < maze.size(); i++) {
            visited.push_back({});
            for (int j = 0; j < maze[0].size(); j++) {
                visited[i].push_back(false);
            }
        }
        return dfs(start, destination, maze, visited);
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    bool dfs(vector<int> start, vector<int> &end, vector<vector<int>> &maze, vector<vector<bool>> &visited) {
        if (visited[start[0]][start[1]]) return false;
        visited[start[0]][start[1]] = true;

        if (start == end) return true;

        // try all four directions
        for (int dir = 0; dir < 4; dir++) {
            int ballRow = start[0];
            int ballCol = start[1];

            // find a wall
            while (true) {
                ballRow += dy[dir];
                ballCol += dx[dir];
                // out of bounds means wall
                if (ballRow < 0 || ballCol < 0 || ballRow >= maze.size() || ballCol >= maze[0].size()) {
                    ballRow -= dy[dir];
                    ballCol -= dx[dir];
                    break;
                }
                // if actually hit a wall
                if (maze[ballRow][ballCol] == 1) {
                    ballRow -= dy[dir];
                    ballCol -= dx[dir];
                    break;
                }
                // otherwise continue rolling ball in direction
            }

            // ball row and col are now right before a wall
            bool success = dfs({ballRow, ballCol}, end, maze, visited);
            if (success) return true;
        }
        return false;
    }
};