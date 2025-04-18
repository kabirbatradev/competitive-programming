#include <bits/stdc++.h>
#define int long long
// #define INT_MAX LLONG_MAX
#define INF 1e18
using namespace std;

int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

struct Solution {
  int r, c; 
  Solution() {
    cin >> r >> c;

    // 2 extra rows: 0s top, 0s bottom
    vector<vector<int>> grid(r+2, vector<int>(c, 0));

    for (int i = 0; i < c; i++) {
      char dummy;
      cin >> dummy;
    }

    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        int x; cin >> x;
        grid[i+1][j] = x;
      }
    }

    for (int i = 0; i < c; i++) {
      char dummy;
      cin >> dummy;
    }

    r += 2;


    vector<vector<bool>> visited(r, vector<bool>(c, false));
    vector<vector<int>> gotHereWeight(r, vector<int>(c, INF));


    // dijkstras maybe
    // total path weight, i, j of cell 
    // max heap by default, so turn it into min
    using thing = tuple<int, int, int>;
    priority_queue<tuple<int, int, int>, vector<thing>, greater<thing>> pq;

    // add the top node to pq top left
    // actually start at bottom
    pq.push({0, r-1, 0}); // weight is 0, start at bottom, 

    int peakWeight = 0;

    while (!pq.empty()) {
      auto [weight, i, j] = pq.top(); pq.pop();

      // update peak weight
      peakWeight = max(peakWeight, weight);

      // catch "reached bottom"
      // row = bottom r+2 rows total -1 for last row
      // end at top not bottom
      if (i == 0) {
        break;
      }

      // catch negative cycle:
      // if visited, then 
      // if its negative, then ask for weight when we were there before
      // if weight now is better, then negative cycle
      if (visited[i][j]) {
        // found cycle
        if (weight < gotHereWeight[i][j]) {
          break;
        }
        // just normal visited
        continue;
      }
      
      visited[i][j] = true;
      gotHereWeight[i][j] = weight;

      // go in 4 directions
      for (int k = 0; k < 4; k++) {
        // do not go if out of bounds
        // but still consider if visited 

        int iNew = i + dx[k];
        int jNew = j + dy[k];

        if (iNew < 0 || jNew < 0 || iNew >= r || jNew >= c) {
          continue;
        }

        // we should skip if visited and not negative as well, right?
        // no then we would lose some longer negative cycles

        // weight is weight so far + grid weight
        pq.push({weight + grid[iNew][jNew], iNew, jNew});
      }
    }

    cout << peakWeight << '\n';
    
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
grid of numbers
start from bottom row anywhere, want to reach top row anywhere
can go up down left right (4 directions)

there can be negative cycles

goal: min energy needed to reach top
if no negatives, then this is just shortest path

if negatives, then this is shortest path to the negative cycle itself

lets run dijstras
mark nodes as visited
but if we want to visit something that is visited and its negative...
at every visited node, store how much energy it took to get there
if we can get to a negative visited node with less energy than the first time, then its a negative cycle
  can return early because every other path is longer

if if no negative cycle, then just wait until we reach top, in which thats just shortest path

*/