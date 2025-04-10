// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
#define int long long
using namespace std;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

struct Solution {
    
  int r, c; 
  int trueC;
  vector<vector<int>> grid;

  Solution() {
    cin >> r >> c;

    // dummy left and right columns
    trueC = c+2;
    grid.assign(r, vector<int>(trueC, -1));

    int low = 1'000'000;
    int high = 0;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        int depth; cin >> depth;

        // offset column by 1 to make space for dummy column
        grid[i][j+1] = depth;

        high = max(depth, high);
        low = min(depth, low);
      }
    }

    // BSTA:
    // int low = 0;
    // int high = 1'000'000;
    int best = high;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      // success: try smaller max depth
      if (canFunction(mid)) {
        best = min(best, mid); // update optimal depth so far
        high = mid - 1;
      }
      // fail: try larger max depth
      else {
        low = mid + 1;
      }
    }

    cout << best << '\n';

  }

  // run bfs to see if we can get from left dummy column to right dummy column with max depth restriction
  bool canFunction(int maxDepth) {

    vector<vector<bool>> visited(r, vector<bool>(trueC, false));
    
    queue<pair<int, int>> q;

    q.push({0, 0}); // start somewhere in left dummy col

    while (!q.empty()) {
      auto [row, col] = q.front(); q.pop();

      if (visited[row][col]) continue;
      visited[row][col] = true;

      // if last column, we reached right dummy column, so its possible!
      if (col == trueC-1) {
        return true;
      }

      // attempt to go in all four directions:
      for (int k = 0; k < 4; k++) {
        int newRow = row + dx[k];
        int newCol = col + dy[k];

        // skip if out of bounds or visited or too much depth
        if (newRow < 0 || newCol < 0 || newRow >= r || newCol >= trueC
          || visited[newRow][newCol] || grid[newRow][newCol] > maxDepth
        ) {
          continue;
        }

        // add to queue to consider this new position
        q.push({newRow, newCol});
      }
    }

    // BFS ended but we never made it to the right side
    return false;
  }
};

signed main() {
  std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  // cout.precision(1); cout << fixed; // # decimal places

  // int t; cin >> t;
  // for (int i = 0; i < t; i++) 
    Solution s;
}

/*
problem statement: 
need to get from left side to right side
minimize the max depth
can go up down left right

idea:
BSTA for the max depth we can cross
run DFS from left side and see if right side is reachable
actually bfs so it fits in one function

trick:
create column of -1 on left side
create column of -1 on right side

start at top left 
simply ask if bottom right cell is reachable
given a max depth we can go through
*/