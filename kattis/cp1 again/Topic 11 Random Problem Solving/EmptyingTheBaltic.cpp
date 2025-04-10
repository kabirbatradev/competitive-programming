// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
#define int long long
using namespace std;

int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

using node = tuple<int, int, int>;

struct Solution {
  Solution() {
    int h, w; cin >> h >> w;

    // read in the grid
    vector<vector<int>> grid(h, vector<int>(w));
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        cin >> grid[i][j];
      }
    }

    // drain point should be first pq node
    int r, c; cin >> r >> c;
    r--; c--; // problem statement provides 1 indexed values
    int weight = -grid[r][c];

    // weight, row, column
    priority_queue<node> pq;
    pq.push({weight, r, c});

    // visited grid to not drain from same cell twice
    vector<vector<bool>> visited(h, vector<bool>(w, false));

    int totalWater = 0;

    while (!pq.empty()) {
      auto [weight, r, c] = pq.top(); pq.pop();
      
      // skip if alr visited
      if (visited[r][c]) continue;
      visited[r][c] = true;

      // the weight is the water that we get out of this cell
      totalWater += weight;

      // try all 8 directions
      for (int k = 0; k < 8; k++) {
        int rNew = r + dx[k];
        int cNew = c + dy[k];

        // skip if out of bounds or visited or its land (0 or greater)
        if (rNew < 0 || cNew < 0 || rNew >= h || cNew >= w
          || visited[rNew][cNew] || grid[rNew][cNew] >= 0
        ) continue;

        int bottleNeckWeight = min(-grid[rNew][cNew], weight);
        pq.push({bottleNeckWeight, rNew, cNew});
      }
    }

    cout << totalWater << '\n';

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
problem: 
how much water would be drained if we started at a cell
every cell has a different height
water can flow to same or lower height

idea:
use pq:
  weight is how much water the cell would bring into the start cell
  prioritize larger weight paths
  weight is bottlenecked by the cell it comes from or the cell itself

*/