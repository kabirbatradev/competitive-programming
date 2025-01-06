struct Pos {
    int h;
    int r;
    int c;
    Pos(int h, int r, int c) : h(h), r(r), c(c) {}
};

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {

        // pq default max heap --> "<"
        // want min heap --> ">"
        auto compare = [](Pos a, Pos b) {
            return a.h > b.h;
        };
        priority_queue<Pos, vector<Pos>, decltype(compare)> pq(compare);

        int n = grid.size();

        int t = max(grid[0][0], grid.back().back());

        vector<vector<bool>> visited(n, vector<bool>(n, false));

        // push the top left
        pq.push(Pos(grid[0][0], 0, 0));

        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};

        while (true) {
            if (pq.top().h <= t) {
                Pos p = pq.top();
                pq.pop();

                // skip if already visited
                if (visited[p.r][p.c]) continue;

                // if bottom right, then return t
                if (p.r == n-1 && p.c == n-1) return t;

                // mark as visited
                visited[p.r][p.c] = true;

                // push neighbors if not visited
                for (int k = 0; k < 4; k++) {
                    int r2 = p.r + dx[k];
                    int c2 = p.c + dy[k];

                    // only push neighbor if not out of bounds and not visited
                    if (r2 < 0 || c2 < 0 || r2 >= n || c2 >= n || visited[r2][c2]) {
                        continue;
                    }

                    pq.push(Pos(grid[r2][c2], r2, c2));
                }
            }
            else {
                t = pq.top().h;
            }
        }

        return -1;
    }
};

// problem rephrased: at what time is top left and bottom right "connected"
// path is unblocked if t >= height

// interesting note: 
    // grid values are unique
    // grid is n by n
    // grid value is at most n^2 = 50^2 = 2500

// idea 1: 
// put neighbors into pq
// explore if height value <= current t
// if can no longer explore, then increment t to the next height value required
// if reach bottom right, then win!
// runtime: 
    // might go through all n^2 nodes
    // sorting with pq would take n^2 * log(n^2)
// minor optimization: initialize t to max(top left, bottom right)